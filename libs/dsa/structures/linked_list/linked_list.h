#include "node.h"

namespace dsa::structures::linked_list
{
    template<typename T>
    class LinkedList
    {
        private:
            using ValueType = T;                    /// Type of value.
            using ReferenceType = T&;               /// Reference type of value.
            using PointerType = T*;                 /// Pointer type of value.
            using ConstReferenceType = const T&;    /// Const reference type to value.

            Node<ValueType>* pStart;                /// Pointer to first node.
            Node<ValueType>* pEnd;                  /// Pointer to last node.
            size_t mSize;                           /// Allocated nodes count.

        public:
            /**
             * @brief Default constructor. Sets attributes.
             */
            LinkedList() : pStart(nullptr), pEnd(nullptr), mSize(0) {}

            /**
             * @brief Parametric constructor. Takes value and allocate first node.
             * @param data Value to set into first node.
             */
            LinkedList(ValueType data) : pStart(new Node<ValueType>(data)), pEnd(pStart), mSize(1) {}

            /**
             * @brief Parametric constructor. Takes pointer to first node and sets every attribute accordingly.
             * @param start Pointer to first node of linked list.
             */
            LinkedList(Node<ValueType>* start) : pStart(start), mSize(0)
            {
                Node<ValueType>* currentNode = start;

                while (currentNode != nullptr)
                {
                    this->mSize++;

                    if (currentNode->getNextNode() == nullptr)
                        break;

                    currentNode = currentNode->getNextNode();
                }

                this->pEnd = currentNode;
            }

            /**
             * @brief Copy constructor. Creates deep copy of another Node instance.
             * @param other Other Node instance.
             */
            LinkedList(const LinkedList<ValueType>& other) 

    };
}
