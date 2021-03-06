#pragma once


#include "../BaseLibrary/Graph/NodeFactory.hpp"


namespace inl {
namespace gxeng {


class GraphicsEngine;


class GraphicsNodeFactory : public NodeFactory {
public:
	NodeBase* CreateNode(const std::string& name) const override;

private:
	GraphicsEngine* m_engine;
};


}
}

