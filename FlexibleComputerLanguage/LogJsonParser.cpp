//
// Created by AfazD on 31-Oct-19.
//

#include "LogJsonParser.h"
#include "MemMan.h"
#include "Node.h"
#include "MetaData.h"
#include "Strings.h"
#include "Entity.h"
#include "easylogging++.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "json.hpp"


using json = nlohmann::json;


// Michelle -Added the functionality of creating the Node tree for any type of JSON format log file
Node *LogJsonParser::LogJSONToNodeTree(std::string jsonString) {
    int id = 0;
    rapidjson::Document logs;
    logs.Parse(jsonString.c_str());
    Node *root = MemoryManager::Inst.CreateNode(++id);
    root->SetCustomString("root");
    for (rapidjson::Value::ConstValueIterator itr = logs.Begin(); itr != logs.End(); ++itr) {

        for (rapidjson::Value::ConstMemberIterator tps = itr->MemberBegin(); tps != itr->MemberEnd(); ++tps) {
            Node *currentNode = MemoryManager::Inst.CreateNode(++id);
            //std::cout << tps->name.GetString() << "\n";
            currentNode->SetValue((char *) tps->name.GetString());
            char *val = (char *) tps->name.GetString();
            currentNode->SetCustomString(val);
            rapidjson::Value &jsonvalue = (rapidjson::Value &) (itr->GetObjectA()[tps->name.GetString()]);
            currentNode = LogJsonParser::LOGJSONToNodeTreeRecursively(jsonvalue, currentNode);
            root->AppendNode(currentNode);
        }

    }

    return root;
}


Node *LogJsonParser::LOGJSONToNodeTreeRecursively(rapidjson::Value &j, Node *parent) {

    int id = 0;
    for (rapidjson::Value::ConstMemberIterator data = j.MemberBegin(); data != j.MemberEnd(); data++) {
        rapidjson::Value &jsonvalue = j[data->name.GetString()];
        if (jsonvalue.IsObject()) {
            //std::cout<<"\t"<<data->name.GetString()<<"\n";
            Node *dataNode = MemoryManager::Inst.CreateNode(++id);
            dataNode->SetValue((char *) data->name.GetString());
            char *val = (char *) data->name.GetString();
            dataNode->SetCustomString(val);
            parent->AppendNode(dataNode);
            LOGJSONToNodeTreeRecursively(jsonvalue, dataNode);
        } else if (jsonvalue.IsArray()) {
            int iter = 0;
            for (rapidjson::Value::ConstValueIterator data = jsonvalue.Begin(); data != jsonvalue.End(); ++data) {
                rapidjson::Value &jsonvalue = (rapidjson::Value &) (*data);
                if (jsonvalue.IsObject() || jsonvalue.IsArray()) {
                    LOGJSONToNodeTreeRecursively((rapidjson::Value &) jsonvalue, parent);
                }
                ++iter;
            }
        } else {
            //std::cout<<"\t not object : "<<data->name.GetString()<<"\n";
            Node *dataNode = MemoryManager::Inst.CreateNode(++id);
            dataNode->SetValue((char *) data->name.GetString());
            char *val = (char *) data->name.GetString();
            dataNode->SetCustomString(val);
            Node *valueNode = MemoryManager::Inst.CreateNode(++id);
            valueNode->SetValue((char *) (data->value.GetString()));
            char *val1 = (char *) data->value.GetString();
            valueNode->SetCustomString(val1);
            dataNode->AppendNode(valueNode);
            parent->AppendNode(dataNode);
        }
    }

    return parent;
}
// End of the creating the Node tree for any type of JSON format log file functionality

// Michelle - added the functionality of printing the Node tree into a file

void LogJsonParser::LogNodeTreetoJson(Node *node) {
    std::ofstream newjsonfile;
    newjsonfile.open("../FlexibleComputerLanguage/maskedJSON.json");
    Node *curr = node->GetFirstChild();
    newjsonfile << _MSTR([{) << _MSTR(\n);
    bool hasChild = false;
    while (curr) {
        PrintNodeToFile(newjsonfile, curr, hasChild);
        if (curr->GetRightSibling()) {
            newjsonfile << "},\n";
        }
        curr = curr->GetRightSibling();
    }
    newjsonfile << _MSTR(\n) << _MSTR(}]);
    newjsonfile.close();
}

//Afaz - Prints the node tree to a json file in json object format using a recursive function
void LogJsonParser::PrintNodeToFile(std::ofstream &newjsonfile, Node *node, int count) {
    MSTRING nodeValue = node->GetValue();
    json j1 = nodeValue;
    if (node->GetChildCount() > 0) {
        if (nodeValue == "Value") {
            newjsonfile << j1 << _MSTR(:);
        } else {
            newjsonfile << j1 << _MSTR(:) << _MSTR({ \n);
        }
    } else {
        newjsonfile << j1 << _MSTR(\n);
    }

    PNODE child = node->GetFirstChild();
    bool hasChildren = false;
    while (child != NULL) {
        hasChildren = true;
        PrintNodeToFile(newjsonfile, child, count);
        if (child->GetRightSibling()) {
            newjsonfile << "},\n";
        }
        child = child->GetRightSibling();
    }
}

//Starting method to parse a common json to node tree
Node *LogJsonParser::CommonJSONToNodeTree(std::string jsonString) {
    int id = 0;
    rapidjson::Document logs;
    logs.Parse(jsonString.c_str());
    Node *root = MemoryManager::Inst.CreateNode(++id);
    root->SetCustomString("root");

    if(logs.IsArray()) {
        for (rapidjson::Value::ConstValueIterator itr = logs.Begin(); itr != logs.End(); ++itr) {
            for (rapidjson::Value::ConstMemberIterator tps = itr->MemberBegin(); tps != itr->MemberEnd(); ++tps) {
                Node *currentNode = MemoryManager::Inst.CreateNode(++id);
                currentNode->SetValue((char *) tps->name.GetString());
                currentNode->SetCustomString((char *) tps->name.GetString());
                rapidjson::Value &jsonvalue = (rapidjson::Value &) (itr->GetObjectA()[tps->name.GetString()]);
                currentNode = LogJsonParser::CommonJSONToNodeTreeRecursively(jsonvalue, currentNode);
                root->AppendNode(currentNode);
            }
        }
    }

    else {
        for (rapidjson::Value::ConstMemberIterator tps = logs.MemberBegin(); tps != logs.MemberEnd(); ++tps) {
            Node *currentNode = MemoryManager::Inst.CreateNode(++id);
            currentNode->SetValue((char *) tps->name.GetString());
            currentNode->SetCustomString( (char *) tps->name.GetString());
            rapidjson::Value &jsonvalue = (rapidjson::Value &) (logs[tps->name.GetString()]);
            currentNode = LogJsonParser::CommonJSONToNodeTreeRecursively(jsonvalue, currentNode);
            root->AppendNode(currentNode);
        }
    }
    return root;
}

Node *LogJsonParser::CommonJSONToNodeTreeRecursively(rapidjson::Value &j, Node *parent) {
    int id = 0;
    if (j.IsObject()) {
        for (rapidjson::Value::ConstMemberIterator data = j.MemberBegin(); data != j.MemberEnd(); data++) {
            rapidjson::Value &jsonvalue = j[data->name.GetString()];
            if (jsonvalue.IsObject()) {
                Node *dataNode = MemoryManager::Inst.CreateNode(++id);
                dataNode->SetValue((char *) data->name.GetString());
                dataNode->SetCustomString((char *) data->name.GetString());
                parent->AppendNode(dataNode);
                CommonJSONToNodeTreeRecursively(jsonvalue, dataNode);
            } else if (jsonvalue.IsArray()) {
                int iter = 0;
                for (rapidjson::Value::ConstValueIterator data = jsonvalue.Begin(); data != jsonvalue.End(); ++data) {
                    rapidjson::Value &jsonvalue = (rapidjson::Value &) (*data);
                    if (jsonvalue.IsObject() || jsonvalue.IsArray()) {
                        CommonJSONToNodeTreeRecursively((rapidjson::Value &) jsonvalue, parent);
                    }
                    ++iter;
                }
            } else {
                if (data->value.IsString()) {
                    PString pStr = 0;
                    MemoryManager::Inst.CreateObject(&pStr);
                    Node *dataNode = MemoryManager::Inst.CreateNode(++id);
                    pStr->SetValue(data->name.GetString());
                    dataNode->SetEntityObj((PENTITY) pStr);
                    dataNode->SetValue((char *) data->name.GetString());
                    dataNode->SetCustomString((char *) data->name.GetString());
                    Node *valueNode = MemoryManager::Inst.CreateNode(++id);
                    valueNode->SetEntityObj((PENTITY) pStr);
                    valueNode->SetValue((char *) data->value.GetString());
                    valueNode->SetCustomString((char *) data->value.GetString());
                    dataNode->AppendNode(valueNode);
                    parent->AppendNode(dataNode);
                } else if (data->value.IsBool()) {
                    PString pStr = 0;
                    MemoryManager::Inst.CreateObject(&pStr);
                    Node *dataNode = MemoryManager::Inst.CreateNode(++id);
                    if (data->value.GetBool()) {
                       pStr->SetValue("true");
                        dataNode->SetValue((char *) data->name.GetString());
                        dataNode->SetEntityObj((PENTITY) pStr);
                        char *val = "true";
                        dataNode->SetCustomString(val);
                        Node *valueNode = MemoryManager::Inst.CreateNode(++id);
                        valueNode->SetEntityObj((PENTITY) pStr);
                        valueNode->SetValue("true");
                        char *val1 = "true";
                        valueNode->SetCustomString(val1);
                        dataNode->AppendNode(valueNode);
                        parent->AppendNode(dataNode);
                    } else {
                        pStr->SetValue("false");
                        dataNode->SetValue((char *) data->name.GetString());
                        dataNode->SetEntityObj((PENTITY) pStr);
                        char *val = "false";
                        dataNode->SetCustomString(val);
                        Node *valueNode = MemoryManager::Inst.CreateNode(++id);
                        valueNode->SetEntityObj((PENTITY) pStr);
                        valueNode->SetValue("false");
                        char *val1 = "false";
                        valueNode->SetCustomString(val1);
                        dataNode->AppendNode(valueNode);
                        parent->AppendNode(dataNode);
                    }

                }
                else if (data->value.IsInt())
                {
                    PString pStr = 0;
                    MemoryManager::Inst.CreateObject(&pStr);
                    Node *dataNode = MemoryManager::Inst.CreateNode(++id);
                    int value = data->value.GetInt();
                    dataNode->SetValue((char *) data->name.GetString());
                    pStr->SetValue(std::to_string(value));
                    dataNode->SetEntityObj((PENTITY) pStr);
                    dataNode->SetCustomString((char *) data->name.GetString());
                    Node *valueNode = MemoryManager::Inst.CreateNode(++id);
                    valueNode->SetEntityObj((PENTITY) pStr);
                    valueNode->SetValue((char *)std::to_string(value).c_str());
                    valueNode->SetCustomString((char *)std::to_string(value).c_str());
                    dataNode->AppendNode(valueNode);
                    parent->AppendNode(dataNode);
                }
                else if(data->value.IsFloat()){
                    PString pStr = 0;
                    MemoryManager::Inst.CreateObject(&pStr);
                    Node *dataNode = MemoryManager::Inst.CreateNode(++id);
                    float value = data->value.GetFloat();
                    pStr->SetValue(std::to_string(value));
                    dataNode->SetEntityObj((PENTITY) pStr);
                    dataNode->SetValue((char *) data->name.GetString());
                    dataNode->SetCustomString((char *) data->name.GetString());
                    Node *valueNode = MemoryManager::Inst.CreateNode(++id);
                    valueNode->SetEntityObj((PENTITY) pStr);
                    valueNode->SetValue((char *)std::to_string(value).c_str());
                    valueNode->SetCustomString((char *)std::to_string(value).c_str());
                    dataNode->AppendNode(valueNode);
                    parent->AppendNode(dataNode);
                }
                else if(data->value.IsDouble()){
                    PString pStr = 0;
                    MemoryManager::Inst.CreateObject(&pStr);
                    Node *dataNode = MemoryManager::Inst.CreateNode(++id);
                    float value = data->value.GetDouble();
                    pStr->SetValue(std::to_string(value));
                    dataNode->SetEntityObj((PENTITY) pStr);
                    dataNode->SetValue((char *) data->name.GetString());
                    dataNode->SetCustomString((char *) data->name.GetString());
                    Node *valueNode = MemoryManager::Inst.CreateNode(++id);
                    valueNode->SetEntityObj((PENTITY) pStr);
                    valueNode->SetValue((char *)std::to_string(value).c_str());
                    valueNode->SetCustomString((char *)std::to_string(value).c_str());
                    dataNode->AppendNode(valueNode);
                    parent->AppendNode(dataNode);
                }

            }
        }
    } else if (j.IsArray()) {
        for (rapidjson::Value::ConstValueIterator data = j.Begin(); data != j.End(); data++) {
            rapidjson::Value &jsonvalue = (rapidjson::Value &) (*data);
            if (jsonvalue.IsObject()) {
                Node *dataNode = MemoryManager::Inst.CreateNode(++id);
                dataNode->SetValue((char *) std::to_string(id).c_str());
                dataNode->SetCustomString((char *) std::to_string(id).c_str());
                parent->AppendNode(dataNode);
                CommonJSONToNodeTreeRecursively(jsonvalue, dataNode);

            } else if (jsonvalue.IsArray()) {
                int iter = 0;
                for (rapidjson::Value::ConstValueIterator data = jsonvalue.Begin(); data != jsonvalue.End(); ++data) {
                    rapidjson::Value &jsonvalue = (rapidjson::Value &) (*data);
                    if (jsonvalue.IsObject() || jsonvalue.IsArray()) {
                        CommonJSONToNodeTreeRecursively((rapidjson::Value &) jsonvalue, parent);
                    }
                    ++iter;
                }
            } else {
                if (j.IsString()) {
                    PString pStr = 0;
                    MemoryManager::Inst.CreateObject(&pStr);
                    Node *dataNode = MemoryManager::Inst.CreateNode(++id);
                    pStr->SetValue(j.GetString());
                    dataNode->SetEntityObj((PENTITY) pStr);
                    dataNode->SetValue((char *) j.GetString());
                    dataNode->SetCustomString((char *) j.GetString());
                    Node *valueNode = MemoryManager::Inst.CreateNode(++id);
                    valueNode->SetEntityObj((PENTITY) pStr);
                    valueNode->SetValue((char *) j.GetString());
                    valueNode->SetCustomString((char *) j.GetString());
                    dataNode->AppendNode(valueNode);
                    parent->AppendNode(dataNode);
                } else if (j.IsBool()) {
                    PString pStr = 0;
                    MemoryManager::Inst.CreateObject(&pStr);
                    Node *dataNode = MemoryManager::Inst.CreateNode(++id);
                    if (j.GetBool()) {
                        pStr->SetValue("true");
                        dataNode->SetEntityObj((PENTITY) pStr);
                        dataNode->SetValue("true");
                        char *val = "true";
                        dataNode->SetCustomString(val);
                        Node *valueNode = MemoryManager::Inst.CreateNode(++id);
                        valueNode->SetValue("true");
                        char *val1 = "true";
                        valueNode->SetEntityObj((PENTITY) pStr);
                        valueNode->SetCustomString(val1);
                        dataNode->AppendNode(valueNode);
                        parent->AppendNode(dataNode);
                    } else {
                        pStr->SetValue("false");
                        dataNode->SetEntityObj((PENTITY) pStr);
                        dataNode->SetValue("false");
                        char *val = "false";
                        dataNode->SetCustomString(val);
                        Node *valueNode = MemoryManager::Inst.CreateNode(++id);
                        valueNode->SetValue("false");
                        char *val1 = "false";
                        valueNode->SetEntityObj((PENTITY) pStr);
                        valueNode->SetCustomString(val1);
                        dataNode->AppendNode(valueNode);
                        parent->AppendNode(dataNode);
                    }

                }
                else if (j.IsInt())
                {
                    PString pStr = 0;
                    MemoryManager::Inst.CreateObject(&pStr);
                    Node *dataNode = MemoryManager::Inst.CreateNode(++id);
                    int value = j.GetInt();
                    pStr->SetValue(std::to_string(value));
                    dataNode->SetEntityObj((PENTITY) pStr);
                    dataNode->SetValue((char *)std::to_string(value).c_str());
                    dataNode->SetCustomString((char *)std::to_string(value).c_str());
                    Node *valueNode = MemoryManager::Inst.CreateNode(++id);
                    valueNode->SetEntityObj((PENTITY) pStr);
                    valueNode->SetValue((char *)std::to_string(value).c_str());
                    valueNode->SetCustomString((char *)std::to_string(value).c_str());
                    dataNode->AppendNode(valueNode);
                    parent->AppendNode(dataNode);
                }
                else if(j.IsFloat()){
                    PString pStr = 0;
                    MemoryManager::Inst.CreateObject(&pStr);
                    Node *dataNode = MemoryManager::Inst.CreateNode(++id);
                    float value = j.GetFloat();
                    pStr->SetValue(std::to_string(value));
                    dataNode->SetEntityObj((PENTITY) pStr);
                    dataNode->SetValue((char *)std::to_string(value).c_str());
                    dataNode->SetCustomString((char *)std::to_string(value).c_str());
                    Node *valueNode = MemoryManager::Inst.CreateNode(++id);
                    valueNode->SetEntityObj((PENTITY) pStr);
                    valueNode->SetValue((char *)std::to_string(value).c_str());
                    valueNode->SetCustomString((char *)std::to_string(value).c_str());
                    dataNode->AppendNode(valueNode);
                    parent->AppendNode(dataNode);
                }
                else if(j.IsDouble()){
                    PString pStr = 0;
                    MemoryManager::Inst.CreateObject(&pStr);
                    Node *dataNode = MemoryManager::Inst.CreateNode(++id);
                    float value = j.GetDouble();
                    pStr->SetValue(std::to_string(value));
                    dataNode->SetEntityObj((PENTITY) pStr);
                    dataNode->SetValue((char *)std::to_string(value).c_str());
                    dataNode->SetCustomString((char *)std::to_string(value).c_str());
                    Node *valueNode = MemoryManager::Inst.CreateNode(++id);
                    valueNode->SetEntityObj((PENTITY) pStr);
                    valueNode->SetValue((char *)std::to_string(value).c_str());
                    valueNode->SetCustomString((char *)std::to_string(value).c_str());
                    dataNode->AppendNode(valueNode);
                    parent->AppendNode(dataNode);
                }

            }
        }
    } else {

        if (j.IsString()) {
            PString pStr = 0;
            MemoryManager::Inst.CreateObject(&pStr);
            Node *dataNode = MemoryManager::Inst.CreateNode(++id);
            pStr->SetValue(j.GetString());
            dataNode->SetEntityObj((PENTITY) pStr);
            dataNode->SetValue((char *) j.GetString());
            dataNode->SetCustomString((char *) j.GetString());
            Node *valueNode = MemoryManager::Inst.CreateNode(++id);
            valueNode->SetEntityObj((PENTITY) pStr);
            valueNode->SetValue((char *) j.GetString());
            valueNode->SetCustomString((char *) j.GetString());
            dataNode->AppendNode(valueNode);
            parent->AppendNode(dataNode);
        } else if (j.IsBool()) {
            PString pStr = 0;
            MemoryManager::Inst.CreateObject(&pStr);
            Node *dataNode = MemoryManager::Inst.CreateNode(++id);
            if (j.GetBool()) {
                pStr->SetValue("true");
                dataNode->SetEntityObj((PENTITY) pStr);
                dataNode->SetValue("true");
                char *val = "true";
                dataNode->SetCustomString(val);
                Node *valueNode = MemoryManager::Inst.CreateNode(++id);
                valueNode->SetValue("true");
                char *val1 = "true";
                valueNode->SetEntityObj((PENTITY) pStr);
                valueNode->SetCustomString(val1);
                dataNode->AppendNode(valueNode);
                parent->AppendNode(dataNode);
            } else {
                pStr->SetValue("false");
                dataNode->SetEntityObj((PENTITY) pStr);
                dataNode->SetValue("false");
                char *val = "false";
                dataNode->SetCustomString(val);
                Node *valueNode = MemoryManager::Inst.CreateNode(++id);
                valueNode->SetValue("false");
                char *val1 = "false";
                valueNode->SetEntityObj((PENTITY) pStr);
                valueNode->SetCustomString(val1);
                dataNode->AppendNode(valueNode);
                parent->AppendNode(dataNode);
            }

        }
        else if (j.IsInt())
        {
            PString pStr = 0;
            MemoryManager::Inst.CreateObject(&pStr);
            Node *dataNode = MemoryManager::Inst.CreateNode(++id);
            int value = j.GetInt();
            pStr->SetValue(std::to_string(value));
            dataNode->SetEntityObj((PENTITY) pStr);
            dataNode->SetValue((char *)std::to_string(value).c_str());
            dataNode->SetCustomString((char *)std::to_string(value).c_str());
            Node *valueNode = MemoryManager::Inst.CreateNode(++id);
            valueNode->SetEntityObj((PENTITY) pStr);
            valueNode->SetValue((char *)std::to_string(value).c_str());
            valueNode->SetCustomString((char *)std::to_string(value).c_str());
            dataNode->AppendNode(valueNode);
            parent->AppendNode(dataNode);
        }
        else if(j.IsFloat()){
            PString pStr = 0;
            MemoryManager::Inst.CreateObject(&pStr);
            Node *dataNode = MemoryManager::Inst.CreateNode(++id);
            float value = j.GetFloat();
            pStr->SetValue(std::to_string(value));
            dataNode->SetEntityObj((PENTITY) pStr);
            dataNode->SetValue((char *)std::to_string(value).c_str());
            dataNode->SetCustomString((char *)std::to_string(value).c_str());
            Node *valueNode = MemoryManager::Inst.CreateNode(++id);
            valueNode->SetEntityObj((PENTITY) pStr);
            valueNode->SetValue((char *)std::to_string(value).c_str());
            valueNode->SetCustomString((char *)std::to_string(value).c_str());
            dataNode->AppendNode(valueNode);
            parent->AppendNode(dataNode);
        }
        else if(j.IsDouble()){
            PString pStr = 0;
            MemoryManager::Inst.CreateObject(&pStr);
            Node *dataNode = MemoryManager::Inst.CreateNode(++id);
            float value = j.GetDouble();
            pStr->SetValue(std::to_string(value));
            dataNode->SetEntityObj((PENTITY) pStr);
            dataNode->SetValue((char *)std::to_string(value).c_str());
            dataNode->SetCustomString((char *)std::to_string(value).c_str());
            Node *valueNode = MemoryManager::Inst.CreateNode(++id);
            valueNode->SetEntityObj((PENTITY) pStr);
            valueNode->SetValue((char *)std::to_string(value).c_str());
            valueNode->SetCustomString((char *)std::to_string(value).c_str());
            dataNode->AppendNode(valueNode);
            parent->AppendNode(dataNode);
        }
    }
    return parent;
}
//End of the method to parse a common json to node tree





