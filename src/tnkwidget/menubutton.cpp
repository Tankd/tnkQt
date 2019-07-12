#include "menubutton.h"

#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

MenuButton::MenuButton(MenuButton::Type type, QWidget *parent) : QWidget(parent),
    m_type( type)
{
    setMinimumSize(32, 20);
    setMaximumSize(32, 20);
    setMouseTracking( true);


}





void MenuButton::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    if(m_hover)
        painter.fillRect(event->rect(), m_type == CloseButton ? Qt::red : Qt::darkGray);





    auto pen = painter.pen();
    pen.setWidth(2);
    pen.setColor( m_hover ? Qt::white : Qt::darkGray);
    painter.setPen( pen);

    if( m_type == MenuBarButton)
    {
        painter.drawLine(10, height()*0.3, width()-10, height()*0.3);
        painter.drawLine(10, height()*0.5, width()-10, height()*0.5);
        painter.drawLine(10, height()*0.7, width()-10, height()*0.7);
    }

    if( m_type == MinimizeButton)
    {
        painter.drawLine(10, height()/2, width()-10, height()/2);
    }
    else if( m_type == MaximizeButton)
    {
        painter.drawRect(width()/2- height() / 4, height()/2- height() / 4, height() / 2, height() / 2);
    }
    else if( m_type == CloseButton)
    {        
        painter.drawLine(width()/2-5, height()/2-5, width()/2+5, height()/2+5);
        painter.drawLine(width()/2-5, height()/2+5, width()/2+5, height()/2-5);
    }

    QWidget::paintEvent(event);
    painter.end();
}


void MenuButton::enterEvent(QEvent *event)
{
    Q_UNUSED( event)
    m_hover = true;
    update();
}

void MenuButton::leaveEvent(QEvent *event)
{
    Q_UNUSED( event)
    m_hover = false;
    update();
}


void MenuButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED( event)
    emit clicked();
}
