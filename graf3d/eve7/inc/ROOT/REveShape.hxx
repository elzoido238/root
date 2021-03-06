// @(#)root/eve:$Id$
// Author: Matevz Tadel, 2010

/*************************************************************************
 * Copyright (C) 1995-2007, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT7_REveShape
#define ROOT7_REveShape

#include <ROOT/REveElement.hxx>
#include <ROOT/REveVector.hxx>

#include "TAtt3D.h"
#include "TAttBBox.h"
#include "TColor.h"

namespace ROOT {
namespace Experimental {

class REveShape : public REveElementList, public TAtt3D, public TAttBBox {
private:
   REveShape(const REveShape &);            // Not implemented
   REveShape &operator=(const REveShape &); // Not implemented

public:
   typedef std::vector<REveVector2> vVector2_t;
   typedef std::vector<REveVector2>::iterator vVector2_i;

protected:
   Color_t fFillColor; // fill color of polygons
   Color_t fLineColor; // outline color of polygons
   Float_t fLineWidth; // outline width of polygons

   Bool_t fDrawFrame;      // draw frame
   Bool_t fHighlightFrame; // highlight frame / all shape
   Bool_t fMiniFrame;      // draw minimal frame

public:
   REveShape(const char *n = "REveShape", const char *t = "");
   virtual ~REveShape();

   Int_t WriteCoreJson(nlohmann::json &j, Int_t rnr_offset); // override;

   // Rendering parameters.
   virtual void SetMainColor(Color_t color);

   virtual Color_t GetFillColor() const { return fFillColor; }
   virtual Color_t GetLineColor() const { return fLineColor; }
   virtual Float_t GetLineWidth() const { return fLineWidth; }
   virtual Bool_t GetDrawFrame() const { return fDrawFrame; }
   virtual Bool_t GetHighlightFrame() const { return fHighlightFrame; }
   virtual Bool_t GetMiniFrame() const { return fMiniFrame; }

   virtual void SetFillColor(Color_t c) { fFillColor = c; }
   virtual void SetLineColor(Color_t c) { fLineColor = c; }
   virtual void SetLineWidth(Float_t lw) { fLineWidth = lw; }
   virtual void SetDrawFrame(Bool_t f) { fDrawFrame = f; }
   virtual void SetHighlightFrame(Bool_t f) { fHighlightFrame = f; }
   virtual void SetMiniFrame(Bool_t r) { fMiniFrame = r; }

   // ----------------------------------------------------------------

   virtual void CopyVizParams(const REveElement *el);
   virtual void WriteVizParams(std::ostream &out, const TString &var);

   // ----------------------------------------------------------------

   // Abstract function from TAttBBox:
   // virtual void ComputeBBox();

   // Abstract from REveProjectable, overriden in REveElementList:
   // virtual TClass* ProjectedClass(const REveProjection* p) const;

   // ----------------------------------------------------------------

   static Int_t FindConvexHull(const vVector2_t &pin, vVector2_t &pout, REveElement *caller = 0);

   static Bool_t IsBoxOrientationConsistentEv(const REveVector box[8]);
   static Bool_t IsBoxOrientationConsistentFv(const Float_t box[8][3]);

   static void CheckAndFixBoxOrientationEv(REveVector box[8]);
   static void CheckAndFixBoxOrientationFv(Float_t box[8][3]);

   ClassDef(REveShape, 0); // Abstract base-class for 2D/3D shapes.
};

} // namespace Experimental
} // namespace ROOT

#endif
