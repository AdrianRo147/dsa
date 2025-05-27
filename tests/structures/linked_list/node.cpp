#include <dsa/structures/linked_list/node.h>
#include <gtest/gtest.h>

using namespace dsa::structures::linked_list;

class NodeTest : public ::testing::Test
{
    protected:
        void SetUp() override
        {
        }

        void TearDown() override
        {
        }

        void cleanupNodes(Node<int>* head)
        {
            while (head != nullptr)
            {
                Node<int>* temp = head;
                head = head->getNextNode();
                delete temp;
            }
        }
};

TEST_F(NodeTest, DefaultConstructor)
{
    Node<int> node;

    EXPECT_EQ(node.getNextNode(), nullptr);
    EXPECT_EQ(node.getData(), 0);
}

TEST_F(NodeTest, ParametricConstructor)
{
    Node<int> node(42);

    EXPECT_EQ(node.getData(), 42);
    EXPECT_EQ(node.getNextNode(), nullptr);
}

TEST_F(NodeTest, ParametricConstructorString)
{
    Node<std::string> node("hello");

    EXPECT_EQ(node.getData(), "hello");
    EXPECT_EQ(node.getNextNode(), nullptr);
}

TEST_F(NodeTest, CopyConstructorSingleNode)
{
    Node<int> original(100);
    Node<int> copy(original);

    EXPECT_EQ(copy.getData(), 100);
    EXPECT_EQ(copy.getNextNode(), nullptr);

    copy.setData(200);
    EXPECT_EQ(original.getData(), 100);
    EXPECT_EQ(copy.getData(), 200);
}

TEST_F(NodeTest, CopyConstructorLinkedNodes)
{
    Node<int> first(1);
    Node<int>* second = new Node<int>(2);
    Node<int>* third = new Node<int>(3);

    first.setNextNode(second);
    second->setNextNode(third);

    Node<int> copy(first);

    EXPECT_EQ(copy.getData(), 1);
    ASSERT_NE(copy.getNextNode(), nullptr);
    EXPECT_EQ(copy.getNextNode()->getData(), 2);
    ASSERT_NE(copy.getNextNode()->getNextNode(), nullptr);
    EXPECT_EQ(copy.getNextNode()->getNextNode()->getData(), 3);

    EXPECT_NE(copy.getNextNode(), first.getNextNode());

    cleanupNodes(second);
    cleanupNodes(copy.getNextNode());
}

TEST_F(NodeTest, MoveConstructor)
{
    Node<int> original(50);
    Node<int>* next = new Node<int>(60);
    original.setNextNode(next);

    Node<int> moved(std::move(original));

    EXPECT_EQ(moved.getData(), 50);
    EXPECT_EQ(moved.getNextNode(), next);
    EXPECT_EQ(original.getNextNode(), nullptr);

    delete next;
}

TEST_F(NodeTest, SetAndGetData)
{
    Node<int> node;

    node.setData(123);
    EXPECT_EQ(node.getData(), 123);

    const Node<int>& constRef = node;
    EXPECT_EQ(constRef.getData(), 123);
}

TEST_F(NodeTest, SetAndGetNextNode)
{
    Node<int> first(1);
    Node<int>* second = new Node<int>(2);

    first.setNextNode(second);

    EXPECT_EQ(first.getNextNode(), second);
    EXPECT_EQ(first.getNextNode()->getData(), 2);

    const Node<int>& constRef = first;
    EXPECT_EQ(constRef.getNextNode(), second);

    delete second;
}

TEST_F(NodeTest, CopyAssignmentOperator)
{
    Node<int> original(75);
    Node<int> target;

    target = original;

    EXPECT_EQ(target.getData(), 75);
    EXPECT_EQ(target.getNextNode(), nullptr);

    target = target;
    EXPECT_EQ(target.getData(), 75);
}

TEST_F(NodeTest, CopyAssignmentLinkedNodes)
{
    Node<int> original(10);
    Node<int>* second = new Node<int>(20);
    original.setNextNode(second);

    Node<int> target;
    target = original;

    EXPECT_EQ(target.getData(), 10);
    ASSERT_NE(target.getNextNode(), nullptr);
    EXPECT_EQ(target.getNextNode()->getData(), 20);

    EXPECT_NE(target.getNextNode(), original.getNextNode());

    delete second;
    cleanupNodes(target.getNextNode());
}

TEST_F(NodeTest, MoveAssignmentOperator)
{
    Node<int> original(80);
    Node<int>* next = new Node<int>(90);
    original.setNextNode(next);

    Node<int> target;
    target = std::move(original);

    EXPECT_EQ(target.getData(), 80);
    EXPECT_EQ(target.getNextNode(), next);
    EXPECT_EQ(original.getNextNode(), nullptr);

    target = std::move(target);
    EXPECT_EQ(target.getData(), 80);

    delete next;
}

TEST_F(NodeTest, DataAssignmentOperator)
{
    Node<int> node;

    node = 555;

    EXPECT_EQ(node.getData(), 555);
}

TEST_F(NodeTest, StreamOutputOperator)
{
    Node<int> node(42);

    std::ostringstream oss;
    oss << node;

    std::string output = oss.str();
    EXPECT_TRUE(output.find("Data: 42") != std::string::npos);
    EXPECT_TRUE(output.find("Next node pointer:") != std::string::npos);
}

class TestClass
{
    public:
        int value;
        TestClass(int v = 0) : value(v) {}
        bool operator==(const TestClass& other) const { return value == other.value; }
};

std::ostream& operator<<(std::ostream& os, const TestClass& tc)
{
    os << tc.value;
    return os;
}

TEST_F(NodeTest, CustomClassSupport)
{
    TestClass obj(999);
    Node<TestClass> node(obj);

    EXPECT_EQ(node.getData().value, 999);

    TestClass newObj(111);
    node.setData(newObj);
    EXPECT_EQ(node.getData().value, 111);
}

TEST_F(NodeTest, EdgeCases)
{
    Node<int> zeroNode(0);
    EXPECT_EQ(zeroNode.getData(), 0);

    Node<int> negativeNode(-42);
    EXPECT_EQ(negativeNode.getData(), -42);

    Node<int> node1, node2, node3;
    node1 = node2 = node3 = 777;

    EXPECT_EQ(node1.getData(), 777);
    EXPECT_EQ(node2.getData(), 777);
    EXPECT_EQ(node3.getData(), 777);
}

TEST_F(NodeTest, CopyPerformance)
{
    Node<int> head(1);
    Node<int>* current = &head;

    const int chainLength = 100;
    for (int i = 2; i <= chainLength; ++i)
    {
        Node<int>* newNode = new Node<int>(i);
        current->setNextNode(newNode);
        current = newNode;
    }

    Node<int> copy(head);

    Node<int>* copyPtr = &copy;
    Node<int>* originalPtr = &head;

    for (int i = 1; i <= chainLength; ++i)
    {
        ASSERT_NE(copyPtr, nullptr);
        ASSERT_NE(originalPtr, nullptr);
        EXPECT_EQ(copyPtr->getData(), i);
        EXPECT_EQ(originalPtr->getData(), i);

        if (i > 1)
        {
            EXPECT_NE(copyPtr, originalPtr);
        }

        copyPtr = copyPtr->getNextNode();
        originalPtr = originalPtr->getNextNode();
    }

    cleanupNodes(head.getNextNode());
    cleanupNodes(copy.getNextNode());
}
