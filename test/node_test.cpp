#include "rectangle.h"
#include "circle.h"
#include "node.h"
#include <gtest/gtest.h>
#include <memory>
#include <nlohmann/json.hpp>
#include "wx/dcmemory.h"
#include <string>

// Test for node initialization
TEST(NodeTest, Initialization) {
    auto node = std::make_shared<Node>(10);
    EXPECT_EQ(node->value, 10);
    EXPECT_EQ(node->next, nullptr);
    EXPECT_TRUE(node->getChildren().empty());
}

// Test for adding child nodes
TEST(NodeTest, AddChild) {
    auto parent = std::make_shared<Node>(1);
    auto child1 = std::make_shared<Node>(2);
    auto child2 = std::make_shared<Node>(3);

    parent->addChild(child1);
    parent->addChild(child2);

    const auto& children = parent->getChildren();
    ASSERT_EQ(children.size(), 2);
    EXPECT_EQ(children[0]->value, 2);
    EXPECT_EQ(children[1]->value, 3);
}

// Test for retrieving child nodes
TEST(NodeTest, GetChildren) {
    auto parent = std::make_shared<Node>(1);
    auto child = std::make_shared<Node>(2);

    parent->addChild(child);

    const auto& children = parent->getChildren();
    EXPECT_EQ(children.size(), 1);
    EXPECT_EQ(children[0]->value, 2);
}

// Test for generating nodes from JSON
TEST(NodeTest, FromJson) {
    std::string jsonString = R"([
        {
            "type": "rectangle",
            "x": 100,
            "y": 200,
            "width": 100,
            "height": 100,
            "child_arr": [
                {
                    "type": "circle",
                    "x": 50,
                    "y": 50,
                    "radius": 25
                },
                {
                    "type": "rectangle",
                    "x": 150,
                    "y": 150,
                    "width": 50,
                    "height": 50
                }
            ]
        }
    ])";

    auto root = Node::fromJson(jsonString);

    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->value, 0); // Default value since "value" is not in JSON
    EXPECT_EQ(root->getChildren().size(), 2);

    const auto& children = root->getChildren();

    // Check the first child (circle)
    auto circleChild = std::dynamic_pointer_cast<Circle>(children[0]->drawable);
    ASSERT_NE(circleChild, nullptr);
    EXPECT_EQ(circleChild->getX(), 50);
    EXPECT_EQ(circleChild->getY(), 50);
    EXPECT_EQ(circleChild->getRadius(), 25);

    // Check the second child (rectangle)
    auto rectChild = std::dynamic_pointer_cast<Rectangle>(children[1]->drawable);
    ASSERT_NE(rectChild, nullptr);
    EXPECT_EQ(rectChild->getX(), 150);
    EXPECT_EQ(rectChild->getY(), 150);
    EXPECT_EQ(rectChild->getWidth(), 50);
    EXPECT_EQ(rectChild->getHeight(), 50);
}

// Test for reading a circle from a DXF file
TEST(NodeTest, ReadCircleFromDxf) {
    // Path to the test DXF file
    std::string dxfFilePath = "../test/test_dxf/circle.dxf";

    // Parse the DXF file
    std::shared_ptr<Node> rootNode;
    ASSERT_NO_THROW(rootNode = Node::fromDxf(dxfFilePath));

    // Verify the root node is not null
    ASSERT_NE(rootNode, nullptr);

    // Verify the root node has one child
    const auto& children = rootNode->getChildren();
    ASSERT_EQ(children.size(), 1);

    // Verify the child node is a circle
    auto circleNode = children[0];
    ASSERT_NE(circleNode, nullptr);
    auto circleDrawable = std::dynamic_pointer_cast<Circle>(circleNode->drawable);
    ASSERT_NE(circleDrawable, nullptr);

    // Verify the circle's properties
    EXPECT_DOUBLE_EQ(circleDrawable->getX(), 50.0);
    EXPECT_DOUBLE_EQ(circleDrawable->getY(), 50.0);
    EXPECT_DOUBLE_EQ(circleDrawable->getRadius(), 25.0);
}

// Main function for Google Test
int main(int argc, char** argv) {
    // Suppress wxWidgets GUI initialization
    
    ::testing::InitGoogleTest(&argc, argv);

    // Redirect stderr to /dev/null to suppress Gtk-WARNING messages
    int original_stderr = dup(STDERR_FILENO);
    freopen("/dev/null", "w", stderr);

    int result = RUN_ALL_TESTS();

    // Restore stderr
    fflush(stderr);
    dup2(original_stderr, STDERR_FILENO);
    close(original_stderr);

    return result;
}