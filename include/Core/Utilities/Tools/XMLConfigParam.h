/*
Copyright (c) 2017-2018 Origin Quantum Computing. All Right Reserved.
Licensed under the Apache License 2.0

XMLConfigParam.h
Author: Wangjing
Created in 2018-8-31

Classes for get the shortes path of graph

*/
#ifndef XMLCONFIGPARAM_H
#define XMLCONFIGPARAM_H
#include "Core/Utilities/QPandaNamespace.h"
#include "ThirdParty/TinyXML/tinyxml.h"
#include "Core/QuantumCircuit/QGlobalVariable.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>

#define CONFIG_PATH  "./QPandaConfig.xml"

QPANDA_BEGIN

class XmlConfigParam
{
public:
    XmlConfigParam() ;
    bool loadFile(const std::string &filename);
    bool getMetadataConfig(int &qubit_num, std::vector<std::vector<int>> &qubit_matrix);
    bool getClassNameConfig(std::map<std::string, std::string> &class_names);

    bool getQuantumCloudConfig(std::map<std::string, std::string> &cloud_config);
    bool getQGateConfig(std::vector<std::string> &single_gates, std::vector<std::string> &double_gates);
    bool getQGateTimeConfig(std::map<GateType, size_t> &gate_time);
    bool getInstructionConfig(std::map<std::string, std::map<std::string, uint32_t>> &);
    virtual ~XmlConfigParam() {};

	//read topological structure from xml config file
	static bool readAdjacentMatrix(TiXmlElement *AdjacentMatrixElement, int &qubit_num, std::vector<std::vector<int>> &qubit_matrix);

	//load quantum circuit topological structure
	static bool loadQuantumTopoStructure(const std::string &xmlStr, const std::string& dataElementStr, int &qubitsCnt, std::vector< std::vector<int>> &vec, const std::string configFile = "");

	TiXmlElement* get_root_element() { return m_root_element; }

private:
    TiXmlDocument m_doc;
    TiXmlElement *m_root_element;
    std::string m_filename;
};

class TimeSequenceConfig
{
#define Q_GATE_TIME_SEQUENCE_CONFIG ("QGateTimeSequence")
#define Q_MEASURE_TIME_SEQUENCE ("QMeasureTimeSequence")
#define Q_SWAP_TIME_SEQUENCE ("QSwapTimeSequence")
#define Q_CONTROL_GATE_TIME_SEQUENCE ("QGateControlTimeSequence")
#define Q_SINGLE_GATE_TIME_SEQUENCE ("QGateSingleTimeSequence")

public:
	static TimeSequenceConfig& get_instance() {
		static TimeSequenceConfig _instance;
		return _instance;
	}
	~TimeSequenceConfig() {}

	int get_measure_time_sequence();
	int get_ctrl_node_time_sequence();
	int get_swap_gate_time_sequence();
	int get_single_gate_time_sequence();

	template<typename config_type>
	int read_config(config_type type_str, int val) {
		int ret = val; //default val
		if (nullptr != m_config_elem)
		{
			TiXmlElement* tmp_elem = m_config_elem->FirstChildElement(type_str);
			if (nullptr != tmp_elem)
			{
				ret = atoi(tmp_elem->GetText());
			}
		}

		return ret;
	}

private:
	TimeSequenceConfig();

private:
	XmlConfigParam m_config_file;
	TiXmlElement* m_config_elem;
};

QPANDA_END
#endif // XMLCONFIGPARAM_H