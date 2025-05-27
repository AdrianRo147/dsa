#include <iostream>

namespace dsa::structures::linked_list
{
    /**
     * @brief Node of linked list.
     * @tparam T Type of value.
     */
    template<typename T>
    class Node
    {
        private:
            using ValueType = T;                    /// Type of value.
            using ReferenceType = T&;               /// Reference type of value.
            using PointerType = T*;                 /// Pointer type of value.
            using ConstReferenceType = const T&;    /// Const reference type to value.

            ValueType mData;                        /// Data attribute.
            Node<ValueType>* pNext;                 /// Pointer to next node.

        public:
            /**
             * @brief Default constructor. Initializes attributes.
             */
            Node() : pNext(nullptr) {}

            /**
             * @brief Parametric constructor. Initializes attributes.
             * @param data Data to set into attribute.
             */
            Node(ValueType data) : mData(data), pNext(nullptr) {}

            /**
             * @brief Copy constructor. Creates deep copy of another Node instance.
             * @param other Other Node instance.
             */
            Node(const Node<ValueType>& other) : mData(other.mData)
            {
                if (other.pNext == nullptr)
                {
                    this->pNext = nullptr;
                    return;
                }

                Node<ValueType>* newNodes = new Node<ValueType>();

                Node<ValueType>* currentNode = newNodes;
                Node<ValueType>* currentOtherNode = other.pNext;

                while(currentOtherNode != nullptr)
                {
                    currentNode->setData(currentOtherNode->getData());
                    currentNode->pNext = new Node<ValueType>();

                    currentNode = currentNode->pNext;
                    currentOtherNode = currentOtherNode->pNext;
                }

                this->pNext = newNodes;
            }

            /**
             * @brief Move constructor. Transfers ownership of resources from another Node instance.
             * @param other Other Node instance.
             */
            Node(Node<ValueType>&& other) : mData(other.mData), pNext(other.pNext)
            {
                other.pNext = nullptr;
            }

            /**
             * @brief Default destructor.
             *
             * This destructor doesn't do anything, since deallocation is managed by linked_list.h.
             */
            ~Node()
            {
                Node<ValueType>* currentNode = this->pNext;
                Node<ValueType>* nextNode = nullptr;

                while (currentNode != nullptr)
                {
                    nextNode = nextNode->pNext;

                    delete currentNode;

                    currentNode = nextNode;
                }
            }

            /**
             * @brief Sets data.
             * @param data Data to set.
             */
            void setData(ValueType data)
            {
                this->mData = data;
            }

            /**
             * @brief Gets data.
             * @return Value set in data.
             */
            ReferenceType getData()
            {
                return this->mData;
            }

            /**
             * @brief Gets data.
             * @return Value set in data.
             */
            ConstReferenceType getData() const
            {
                return this->mData;
            }

            /**
             * @brief Sets next node.
             * @param next Pointer to next node.
             */
            void setNextNode(Node<ValueType>* next)
            {
                this->pNext = next;
            }

            /**
             * @brief Gets pointer to next node.
             * @return Pointer to next node.
             */
            Node<ValueType>* getNextNode()
            {
                return this->pNext;
            }

            /**
             * @brief Gets pointer to next node.
             * @return Pointer to next node.
             */
            const Node<ValueType>* getNextNode() const
            {
                return this->pNext;
            }

            /**
             * @brief Copy assignment operator.
             *
             * Copies attributes from other Node instance to this Node instance.
             *
             * @param other Node instance to copy from.
             * @return Reference to this Node instance.
             */
            Node<ValueType>& operator=(const Node<ValueType>& other)
            {
                if (this == &other)
                    return *this;

                this->pNext->~Node();

                if (other.pNext == nullptr)
                {
                    this->mData = other.mData;
                    this->pNext = nullptr;

                    return *this;
                }

                Node<ValueType>* newNodes = new Node<ValueType>();

                Node<ValueType>* currentNode = newNodes;
                Node<ValueType>* currentOtherNode = other.pNext;

                while(currentOtherNode != nullptr)
                {
                    currentNode->setData(currentOtherNode->getData());
                    currentNode->pNext = new Node<ValueType>();

                    currentNode = currentNode->pNext;
                    currentOtherNode = currentOtherNode->pNext;
                }

                this->pNext = newNodes;

                return *this;
            }

            /**
             * @brief Move assignment operator.
             *
             * Moves attributes from other Node instance to this Node instance and set other Node instance attributes to null.
             *
             * @param other Node instance to move from.
             * @return Reference to this Node instance.
             */
            Node<ValueType>& operator=(Node<ValueType>&& other) noexcept
            {
                if (this == &other)
                    return *this;

                this->mData = other.mData;
                this->pNext = other.pNext;

                other.pNext = nullptr;

                return *this;
            }

            /**
             * @brief Assignment operator.
             *
             * Sets data attribute.
             *
             * @param data Value to set.
             * @return Reference to this Node instance.
             */
            Node<ValueType>& operator=(ConstReferenceType data)
            {
                this->mData = data;

                return *this;
            }

            /**
             * @brief Outputs content of node to stream.
             * @param os Output stream.
             * @param node Node instance to output.
             * @return Reference to output stream.
             */
            friend std::ostream& operator<<(std::ostream& os, const Node<ValueType>& node)
            {
                os << "Data: " << node.mData << " | Next node pointer: " << node.pNext << std::endl;
                return os;
            }
    };
}
