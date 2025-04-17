#ifndef DXF_INTERFACE_IMPL_H
#define DXF_INTERFACE_IMPL_H

#include "drw_interface.h"
#include "node.h"
#include <memory>
#include <vector>
#include <map>
#include <string>

class DxfInterfaceImpl : public DRW_Interface {
public:
    DxfInterfaceImpl();
    ~DxfInterfaceImpl() override = default;

    // Override pure virtual functions from DRW_Interface
    void addHeader(const DRW_Header* data) override;
    void addLine(const DRW_Line& data) override;
    void addCircle(const DRW_Circle& data) override;
    void addArc(const DRW_Arc& data) override;
    void addPolyline(const DRW_Polyline& data) override;
    void addLWPolyline(const DRW_LWPolyline& data) override;
    void addText(const DRW_Text& data) override;
    void addMText(const DRW_MText& data) override;
    void addPoint(const DRW_Point& data) override;
    void addBlock(const DRW_Block& data) override;
    void setBlock(const int handle) override;
    void endBlock() override;
    void addInsert(const DRW_Insert& data) override;
    void addSpline(const DRW_Spline* data) override;
    void add3dFace(const DRW_3Dface& data) override;
    void addHatch(const DRW_Hatch* data) override;
    void addImage(const DRW_Image* data) override;
    void linkImage(const DRW_ImageDef* data) override;

    // Implement missing pure virtual functions
    void addLType(const DRW_LType& data) override;
    void addLayer(const DRW_Layer& data) override;
    void addDimStyle(const DRW_Dimstyle& data) override;
    void addVport(const DRW_Vport& data) override;
    void addTextStyle(const DRW_Textstyle& data) override;
    void addAppId(const DRW_AppId& data) override;
    void addRay(const DRW_Ray& data) override;
    void addXline(const DRW_Xline& data) override;
    void addEllipse(const DRW_Ellipse& data) override;
    void addKnot(const DRW_Entity& data) override;
    void addTrace(const DRW_Trace& data) override;
    void addSolid(const DRW_Solid& data) override;
    void addDimAlign(const DRW_DimAligned* data) override;
    void addDimLinear(const DRW_DimLinear* data) override;
    void addDimRadial(const DRW_DimRadial* data) override;
    void addDimDiametric(const DRW_DimDiametric* data) override;
    void addDimAngular(const DRW_DimAngular* data) override;
    void addDimAngular3P(const DRW_DimAngular3p* data) override;
    void addDimOrdinate(const DRW_DimOrdinate* data) override;
    void addLeader(const DRW_Leader* data) override;
    void addViewport(const DRW_Viewport& data) override;
    void addComment(const char* comment) override;
    void addPlotSettings(const DRW_PlotSettings* data) override;
    void writeHeader(DRW_Header& data) override;
    void writeBlocks() override;
    void writeBlockRecords() override;
    void writeEntities() override;
    void writeLTypes() override;
    void writeLayers() override;
    void writeTextstyles() override;
    void writeVports() override;
    void writeDimstyles() override;
    void writeObjects() override;
    void writeAppId() override;

    std::shared_ptr<Node> getRootNode() const;

private:
    std::shared_ptr<Node> rootNode;
    std::vector<std::shared_ptr<Node>> nodes;
    std::map<std::string, std::vector<double>> lineTypePatterns; // Added to store line type patterns
};

#endif // DXF_INTERFACE_IMPL_H
