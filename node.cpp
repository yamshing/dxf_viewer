#include "node.h"
#include "rectangle.h"
#include "circle.h"
#include "line.h" // Include the Line class
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <functional> // Add this include for std::function
#include "drw_interface.h"
#include "drw_entities.h"
#include "drw_header.h"
#include "dxf_interface_impl.h"
#include "libdxfrw.h"

using json = nlohmann::json;

// Constructor
Node::Node(int val, std::shared_ptr<Drawable> drawable)
    : value(val), next(nullptr), drawable(drawable) {}

// Destructor
Node::~Node() {}

// Method to add a child node
void Node::addChild(std::shared_ptr<Node> child) { // Update to use shared_ptr
    child_arr.push_back(child);
}

// Method to get child nodes
const std::vector<std::shared_ptr<Node>>& Node::getChildren() const { // Update to return shared_ptr
    return child_arr;
}

// Method to draw the node and its child nodes
void Node::drawTree(const std::function<void(const Drawable&)>& drawCallback) const {
    if (drawable) {
        drawCallback(*drawable); // Use the callback function for drawing
    }
    for (const auto& child : child_arr) {
        if (child) {
            child->drawTree(drawCallback); // Recursively pass the callback
        }
    }
}

// Static method to construct a node tree from a JSON string
std::shared_ptr<Node> Node::fromJson(const std::string& jsonString) {
    json jsonData = json::parse(jsonString);

    std::function<std::shared_ptr<Node>(const json&)> parseNode = [&](const json& nodeData) -> std::shared_ptr<Node> {
        int value = nodeData.value("value", 0);
        int color = nodeData.value("color", 0); // Default color to 0
        std::shared_ptr<Drawable> drawable;

        if (nodeData["type"] == "rectangle") {
            drawable = std::make_shared<Rectangle>(
                nodeData["x"], nodeData["y"], nodeData["width"], nodeData["height"], color);
        } else if (nodeData["type"] == "circle") {
            drawable = std::make_shared<Circle>(
                nodeData["x"], nodeData["y"], nodeData["radius"], color); // Ensure x, y, radius, and color are passed correctly
        } else if (nodeData["type"] == "line") { // Add support for line
            drawable = std::make_shared<Line>(
                nodeData["x1"], nodeData["y1"], nodeData["x2"], nodeData["y2"], color);
        }

        auto node = std::make_shared<Node>(value, drawable);

        if (nodeData.contains("child_arr")) {
            for (const auto& childData : nodeData["child_arr"]) {
                node->addChild(parseNode(childData)); // Pass shared_ptr directly
            }
        }

        return node;
    };

    // If the root is an array, process the first element as the root node
    if (jsonData.is_array() && !jsonData.empty()) {
        return parseNode(jsonData[0]);
    }

    throw std::invalid_argument("Invalid JSON format for Node tree");
}

// Static method to construct a node tree from a DXF file
std::shared_ptr<Node> Node::fromDxf(const std::string& dxfFilePath) {
    DxfInterfaceImpl dxfInterface;

    // Parse the DXF file using dxfRW
    dxfRW reader(dxfFilePath.c_str());
    if (!reader.read(&dxfInterface, true)) { // Pass 'true' for the second argument
        throw std::runtime_error("Failed to parse DXF file: " + dxfFilePath);
    }

    return dxfInterface.getRootNode();
}

// Method to convert the node tree to JSON
json Node::toJson(bool isRoot) const {
    json nodeData;

    if (drawable) {
        if (auto rect = dynamic_cast<Rectangle*>(drawable.get())) {
            nodeData["type"] = "rectangle";
            nodeData["x"] = rect->getX();
            nodeData["y"] = rect->getY();
            nodeData["width"] = rect->getWidth();
            nodeData["height"] = rect->getHeight();
        } else if (auto circle = dynamic_cast<Circle*>(drawable.get())) {
            nodeData["type"] = "circle";
            nodeData["x"] = circle->getX();
            nodeData["y"] = circle->getY();
            nodeData["radius"] = circle->getRadius();
        } else if (auto line = dynamic_cast<Line*>(drawable.get())) { // Add support for line
            nodeData["type"] = "line";
            nodeData["x1"] = line->getX1();
            nodeData["y1"] = line->getY1();
            nodeData["x2"] = line->getX2();
            nodeData["y2"] = line->getY2();
        }
    }

    if (!child_arr.empty()) {
        nodeData["child_arr"] = json::array();
        for (const auto& child : child_arr) {
            if (child) {
                nodeData["child_arr"].push_back(child->toJson(false)); // Pass false for child nodes
            }
        }
    }

    return isRoot ? json::array({nodeData}) : nodeData; // Wrap in array only if it's the root node
}