#pragma once

#include "json.h"
#include <stack>
#include <string>
#include <memory>

namespace bus_catalog {
    namespace detail {
        namespace json {
            namespace builder {

                class KeyContext;
                class DictionaryContext;
                class ArrayContext;

                class Builder {
                public:
                    Node MakeNode(const Node::Value& value_);
                    void AddNode(const Node& node);

                    KeyContext Key(const std::string& key_);
                    Builder& Value(const Node::Value& value);

                    DictionaryContext BeginDict();
                    Builder& EndDict();

                    ArrayContext BeginArray();
                    Builder& EndArray();

                    Node Build();

                private:
                    Node root_;
                    std::vector<std::unique_ptr<Node>> nodes_stack_;
                };

                class BaseContext {
                public:
                    BaseContext(Builder& builder);

                    KeyContext Key(const std::string& Key);
                    Builder& Value(const Node::Value& value);

                    DictionaryContext BeginDict();
                    Builder& EndDict();

                    ArrayContext BeginArray();
                    Builder& EndArray();

                protected:
                    Builder& builder_;
                };

                class KeyContext : public BaseContext {
                public:
                    KeyContext(Builder& builder);

                    KeyContext Key(const std::string& Key) = delete;

                    BaseContext EndDict() = delete;
                    BaseContext EndArray() = delete;

                    DictionaryContext Value(const Node::Value& value);
                };

                class DictionaryContext : public BaseContext {
                public:
                    DictionaryContext(Builder& builder);

                    DictionaryContext BeginDict() = delete;

                    ArrayContext BeginArray() = delete;
                    Builder& EndArray() = delete;

                    Builder& Value(const Node::Value& value) = delete;
                };

                class ArrayContext : public BaseContext {
                public:
                    ArrayContext(Builder& builder);

                    KeyContext Key(const std::string& Key) = delete;

                    Builder& EndDict() = delete;

                    ArrayContext Value(const Node::Value& value);
                };

            }
        }
    }
}