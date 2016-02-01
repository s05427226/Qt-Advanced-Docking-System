#ifndef ADS_CONTAINERWIDGET_H
#define ADS_CONTAINERWIDGET_H

#include <QFrame>
#include <QGridLayout>
#include <QPoint>
#include <QList>
class QSplitter;

#include "ads.h"
#include "section_content.h"
#include "section_widget.h"
#include "floating_widget.h"

ADS_NAMESPACE_BEGIN

// ContainerWidget is the main container to provide the docking
// functionality. It manages mulitple Sections and all possible areas.
class ContainerWidget : public QFrame
{
	Q_OBJECT
	Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)

	friend class SectionWidget;

public:
	explicit ContainerWidget(QWidget *parent = NULL);

	Qt::Orientation orientation() const;
	void setOrientation(Qt::Orientation orientation);

	void dropContent(const InternalContentData& data, SectionWidget* targetSection, DropArea area);

	void addSection(SectionWidget* section);
	void splitSections(SectionWidget* section1, SectionWidget* section2, Qt::Orientation orientation = Qt::Horizontal);
	SectionWidget* sectionAt(const QPoint& pos) const;

	// Drop areas for the ContainerWidget
	QRect outerTopDropRect() const;
	QRect outerRightDropRect() const;
	QRect outerBottomDropRect() const;
	QRect outerLeftDropRect() const;

	// Geometry and state serialization
	QByteArray saveGeometry() const;
	bool restoreGeometry(const QByteArray& data);

protected:
	virtual void paintEvent(QPaintEvent*);
	virtual void contextMenuEvent(QContextMenuEvent*);

private: // Make private!


signals:
	void orientationChanged();

public:
	// Existing sections.
	// SectionWidgets are always visible.
	QList<SectionWidget*> _sections;

	// All currently active Floatingwidgets.
	QList<FloatingWidget*> _floatingWidgets;

	// Layout stuff
	QGridLayout* _mainLayout;
	Qt::Orientation _orientation;   ///< Default orientation of new sections.
	QSplitter* _splitter;           ///< Default/main splitter.
};

ADS_NAMESPACE_END
#endif