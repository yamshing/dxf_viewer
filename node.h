// Header file for the Node class
#ifndef NODE_H
#define NODE_H

#include <vector>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include <functional>
#include "drawable.h"

using json = nlohmann::json;

class Node {
public:
    int value; // Value of the node
    Node* next; // Pointer to the next node
    std::vector<std::shared_ptr<Node>> child_arr; // Vector to store child nodes (shared_ptr used)
    std::shared_ptr<Drawable> drawable; // Smart pointer to a Drawable instance

    // Constructor
    Node(int val, std::shared_ptr<Drawable> drawable = nullptr);

    // Destructor
    ~Node();

    // Method to add a child node
    void addChild(std::shared_ptr<Node> child); // Argument changed to shared_ptr

    // Method to get child nodes
    const std::vector<std::shared_ptr<Node>>& getChildren() const; // Return type changed to shared_ptr

    // Method to call the draw method of the node and its child nodes
    void drawTree(const std::function<void(const Drawable&)>& drawCallback) const; // Update drawTree to use callback

    // Static method to construct a node tree from a JSON string
    //static std::shared_ptr<Node> fromJson(const std::string& jsonString); // Update return type to shared_ptr

    // Static method to construct a node tree from a DXF file
    static std::shared_ptr<Node> fromDxf(const std::string& dxfFilePath); // Add fromDxf method declaration

    // Method to convert the node tree to JSON
    json toJson(bool isRoot = true) const; // Add isRoot parameter with default value
};

#endif // NODE_H