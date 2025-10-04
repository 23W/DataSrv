#pragma once

#include <string>
#include "Id.h"

class Node
{
public:
    Node() {}
    Node(const Node&) = default;
    Node(Node&&) = default;
    Node& operator = (const Node&) = default;
    Node& operator = (Node&&) = default;

    virtual ~Node() {}

    const Id& GetId() const noexcept { return m_id; }
    const std::string& GetName() const noexcept { return m_name; }

    void SetId(const Id& id) { m_id = id; }
    void SetName(const std::string& name) { m_name = name; }

private:

    Id m_id;
    std::string m_name;
};
