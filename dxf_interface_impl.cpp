#include "dxf_interface_impl.h"
#include "line.h"
#include "circle.h"
#include "rectangle.h"
#include "dxf_text.h"

DxfInterfaceImpl::DxfInterfaceImpl() {
    rootNode = std::make_shared<Node>(0); // Create the root node
}

void DxfInterfaceImpl::addHeader(const DRW_Header* data) {
    // Handle DXF header data if needed
}

void DxfInterfaceImpl::addLine(const DRW_Line& data) {
    std::string lineStyle = data.lineType.empty() ? "CONTINUOUS" : data.lineType; // Default to CONTINUOUS if lineType is empty

    auto drawable = std::make_shared<Line>(data.basePoint.x, data.basePoint.y,
                                           data.secPoint.x, data.secPoint.y,
                                           data.color, lineStyle);

    // Set the line style pattern if available
    if (lineTypePatterns.find(lineStyle) != lineTypePatterns.end()) {
        drawable->setLineStylePattern(lineTypePatterns[lineStyle]);
    }

    if (data.lWeight > 0) {
        drawable->setLineWidth(data.lWeight);
    }

    auto node = std::make_shared<Node>(0, drawable);
    nodes.push_back(node);
    rootNode->addChild(node);
}

void DxfInterfaceImpl::addCircle(const DRW_Circle& data) {
    std::string lineStyle = data.lineType.empty() ? "CONTINUOUS" : data.lineType; // Default to CONTINUOUS if lineType is empty

    auto drawable = std::make_shared<Circle>(data.basePoint.x, data.basePoint.y,
                                             data.radious, data.color, lineStyle);

    // Set the line style pattern if available
    if (lineTypePatterns.find(lineStyle) != lineTypePatterns.end()) {
        drawable->setLineStylePattern(lineTypePatterns[lineStyle]);
    }

    // Set the line width from DXF data
    if (data.lWeight > 0) {
        drawable->setLineWidth(data.lWeight); 
    }

    auto node = std::make_shared<Node>(0, drawable);
    nodes.push_back(node);
    rootNode->addChild(node);
}

void DxfInterfaceImpl::addArc(const DRW_Arc& data) {
    // Handle arcs if needed
}

void DxfInterfaceImpl::addPolyline(const DRW_Polyline& data) {
    // Handle polylines if needed
}

void DxfInterfaceImpl::addLWPolyline(const DRW_LWPolyline& data) {
    // Handle lightweight polylines if needed
}

void DxfInterfaceImpl::addText(const DRW_Text& data) {
    auto drawable = std::make_shared<DxfText>(data.text, data.basePoint.x, data.basePoint.y, data.height, data.color); // Parse color from DXF data
    auto node = std::make_shared<Node>(0, drawable);
    nodes.push_back(node);
    rootNode->addChild(node);
}

void DxfInterfaceImpl::addMText(const DRW_MText& data) {
    // Handle multi-line text entities if needed
}

void DxfInterfaceImpl::addPoint(const DRW_Point& data) {
    // Handle points if needed
}

void DxfInterfaceImpl::addBlock(const DRW_Block& data) {
    // Handle blocks if needed
}

void DxfInterfaceImpl::setBlock(const int handle) {
    // Handle block setting if needed
}

void DxfInterfaceImpl::endBlock() {
    // Handle block ending if needed
}

void DxfInterfaceImpl::addInsert(const DRW_Insert& data) {
    // Handle inserts if needed
}

void DxfInterfaceImpl::addSpline(const DRW_Spline* data) {
    // Handle splines if needed
}

void DxfInterfaceImpl::add3dFace(const DRW_3Dface& data) {
    // Handle 3D faces if needed
}

void DxfInterfaceImpl::addHatch(const DRW_Hatch* data) {
    // Handle hatches if needed
}

void DxfInterfaceImpl::addImage(const DRW_Image* data) {
    // Handle images if needed
}

void DxfInterfaceImpl::linkImage(const DRW_ImageDef* data) {
    // Handle image linking if needed
}

void DxfInterfaceImpl::addLType(const DRW_LType& data) {
    std::vector<double> pattern;

    // Parse the dash pattern from the DRW_LType data
    for (double dash : data.path) { // Corrected to use `dashes` instead of `dashList`
        pattern.push_back(dash);
    }

    /*std::cout << "Line Type: " << data.name << " Pattern: ";
    for (const auto& dash : pattern) {
        std::cout << dash << " ";
    }
    std::cout << std::endl;*/

    // Store the pattern in a map for later use
    lineTypePatterns[data.name] = pattern;
}

void DxfInterfaceImpl::addLayer(const DRW_Layer& data) {
    // Handle layers if needed
}

void DxfInterfaceImpl::addDimStyle(const DRW_Dimstyle& data) {
    // Handle dimension styles if needed
}

void DxfInterfaceImpl::addVport(const DRW_Vport& data) {
    // Handle viewports if needed
}

void DxfInterfaceImpl::addTextStyle(const DRW_Textstyle& data) {
    // Handle text styles if needed
}

void DxfInterfaceImpl::addAppId(const DRW_AppId& data) {
    // Handle application IDs if needed
}

void DxfInterfaceImpl::addRay(const DRW_Ray& data) {
    // Handle rays if needed
}

void DxfInterfaceImpl::addXline(const DRW_Xline& data) {
    // Handle xlines if needed
}

void DxfInterfaceImpl::addEllipse(const DRW_Ellipse& data) {
    // Handle ellipses if needed
}

void DxfInterfaceImpl::addKnot(const DRW_Entity& data) {
    // Handle knots if needed
}

void DxfInterfaceImpl::addTrace(const DRW_Trace& data) {
    // Handle traces if needed
}

void DxfInterfaceImpl::addSolid(const DRW_Solid& data) {
    // Handle solids if needed
}

void DxfInterfaceImpl::addDimAlign(const DRW_DimAligned* data) {
    // Handle aligned dimensions if needed
}

void DxfInterfaceImpl::addDimLinear(const DRW_DimLinear* data) {
    // Handle linear dimensions if needed
}

void DxfInterfaceImpl::addDimRadial(const DRW_DimRadial* data) {
    // Handle radial dimensions if needed
}

void DxfInterfaceImpl::addDimDiametric(const DRW_DimDiametric* data) {
    // Handle diametric dimensions if needed
}

void DxfInterfaceImpl::addDimAngular(const DRW_DimAngular* data) {
    // Handle angular dimensions if needed
}

void DxfInterfaceImpl::addDimAngular3P(const DRW_DimAngular3p* data) {
    // Handle 3-point angular dimensions if needed
}

void DxfInterfaceImpl::addDimOrdinate(const DRW_DimOrdinate* data) {
    // Handle ordinate dimensions if needed
}

void DxfInterfaceImpl::addLeader(const DRW_Leader* data) {
    // Handle leaders if needed
}

void DxfInterfaceImpl::addViewport(const DRW_Viewport& data) {
    // Handle viewports if needed
}

void DxfInterfaceImpl::addComment(const char* comment) {
    // Handle comments if needed
}

void DxfInterfaceImpl::addPlotSettings(const DRW_PlotSettings* data) {
    // Handle plot settings if needed
}

void DxfInterfaceImpl::writeHeader(DRW_Header& data) {
    // Handle header writing if needed
}

void DxfInterfaceImpl::writeBlocks() {
    // Handle block writing if needed
}

void DxfInterfaceImpl::writeBlockRecords() {
    // Handle block record writing if needed
}

void DxfInterfaceImpl::writeEntities() {
    // Handle entity writing if needed
}

void DxfInterfaceImpl::writeLTypes() {
    // Handle line type writing if needed
}

void DxfInterfaceImpl::writeLayers() {
    // Handle layer writing if needed
}

void DxfInterfaceImpl::writeTextstyles() {
    // Handle text style writing if needed
}

void DxfInterfaceImpl::writeVports() {
    // Handle viewport writing if needed
}

void DxfInterfaceImpl::writeDimstyles() {
    // Handle dimension style writing if needed
}

void DxfInterfaceImpl::writeObjects() {
    // Handle object writing if needed
}

void DxfInterfaceImpl::writeAppId() {
    // Handle application ID writing if needed
}

std::shared_ptr<Node> DxfInterfaceImpl::getRootNode() const {
    return rootNode;
}
