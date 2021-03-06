/*  QESpectrogram.h
 *
 *  This file is part of the EPICS QT Framework, initially developed at the
 *  Australian Synchrotron.
 *
 *  Copyright (c) 2020 Australian Synchrotron
 *
 *  The EPICS QT Framework is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  The EPICS QT Framework is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with the EPICS QT Framework.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author:
 *    Andrew Starritt
 *  Contact details:
 *    andrews@ansto.gov.au
 */

#ifndef QE_SPECTROGRAM_H
#define QE_SPECTROGRAM_H

#include <QHBoxLayout>
#include <QImage>
#include <QString>
#include <QWidget>
#include <QEAbstract2DData.h>
#include <QEFrameworkLibraryGlobal.h>

/// This class presents 2D data as a spectrogram. The value of each element is
/// mapped to the range 0 to 255, and presented in gray scale (black to white)
/// or with false colour (similar to QEImage).
///
class QE_FRAMEWORK_LIBRARY_SHARED_EXPORT QESpectrogram :
   public QEAbstract2DData
{
   Q_OBJECT

   typedef QEAbstract2DData ParentWidgetClass;

public:
   /// If true, the apply false colour to the data, othewrwise gray scale
   ///
   Q_PROPERTY (bool useFalseColour         READ getUseFalseColour WRITE setUseFalseColour)

   /// Specifies the number of times around the gray/colour scale we map values
   /// in the range minimum to maximum.
   /// Allowed range: 1 .. 10  - note 10 is more than enough.
   /// Default: 1
   ///
   Q_PROPERTY (int scaleWrap               READ getScaleWrap      WRITE setScaleWrap)

public:
   // QESpectrogram context menu values
   //
   enum OwnContextMenuOptions {
      QESPEC_NONE = A2DDCM_SUB_CLASS_WIDGETS_START_HERE,
      QESPEC_USE_FALSE_COLOUR_FLIP,
      QESPEC_SUB_CLASS_WIDGETS_START_HERE
   };


   /// Create without a variable.
   /// Use setDataPvName () and setVariableNameSubstitutions() to define a
   /// variable and, optionally, macro substitutions later.
   ///
   explicit QESpectrogram (QWidget* parent = 0);

   /// Create with a variable (s).
   /// A connection is automatically established.
   /// If macro substitutions are required, create without a variable and
   /// set the variable and macro substitutions after creation.
   ///
   explicit QESpectrogram (const QString& dataVariableName,
                           QWidget* parent = 0);

   explicit QESpectrogram (const QString& dataVariableName,
                           const QString& widthVariableName,
                           QWidget* parent = 0);

   /// Destruction
   virtual ~QESpectrogram ();

public slots:
   void setUseFalseColour (const bool useFalseColour);
   void setScaleWrap (const int scaleWrap);

public:
   bool getUseFalseColour () const;
   int getScaleWrap () const;

protected:
   // Override parent virtual functions.
   //
   QSize sizeHint () const;
   bool eventFilter (QObject* watched, QEvent* event);
   void updateDataVisulation ();   // hook function

   QMenu* buildContextMenu ();                        // Build the specific context menu
   void contextMenuTriggered (int selectedItemNum);   // An action was selected from the context menu

private:
   // Structure used when setting current image. Cribbed from QEImage.
   //
   struct rgbPixel {
      unsigned char p[4]; // R/G/B/Alpha
   };

   typedef rgbPixel RgbPixelMaps [256];

   void commonSetup ();
   void paintSpectrogram ();
   void spectrogramMouseMove (const QPoint& pos);
   rgbPixel getFalseColor (const unsigned char value);  // also sets breakPoint1/2

   QWidget* plotArea;      // internal widget on which we paint.
   QHBoxLayout* layout;    // holds the widget - any layout type will do

   QImage image;

   RgbPixelMaps grayScalePixelMap;
   RgbPixelMaps falseColourPixelMap;

   int breakPoint1;       // first colour scale break point
   int breakPoint2;       // second colour scale break point

   // Property members
   //
   bool mUseFalseColour;
   int mScaleWrap;
};

#endif  // QE_SPECTROGRAM_H
