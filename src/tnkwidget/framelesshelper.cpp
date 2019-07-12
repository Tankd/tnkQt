#include "framelesshelper.h"


#include <QHBoxLayout>
#include <QLabel>
#include "menubutton.h"

MainWindowFl::MainWindowFl(QWidget *parent)
    :QMainWindow (parent)
{

}

void MainWindowFl::apply( )
{
    this->setWindowFlag( Qt::FramelessWindowHint);

    m_titleWidget = new QWidget(this);    
    this->setMenuWidget( m_titleWidget);

    m_titleLayout = new QHBoxLayout();
    m_titleLayout->setMargin(0);
    m_titleWidget->setLayout( m_titleLayout);

    m_iconButton = new MenuButton(MenuButton::MenuBarButton, this);
    m_titleLayout->addWidget( reinterpret_cast<QWidget*>( m_iconButton));

    m_customWidgetLayout = new QHBoxLayout();
    m_titleLayout->addItem(m_customWidgetLayout);


    m_titleLabel = new QLabel( this->windowTitle());
    m_titleLayout->addWidget( reinterpret_cast<QWidget*>( m_titleLabel));
    connect( this, &QMainWindow::windowTitleChanged, m_titleLabel, &QLabel::setText);




    m_minimizeButton = new MenuButton( MenuButton::MinimizeButton, this);
    m_titleLayout->addWidget( reinterpret_cast<QWidget*>( m_minimizeButton));

    m_maximizeButton = new MenuButton( MenuButton::MaximizeButton, this);
    m_titleLayout->addWidget( reinterpret_cast<QWidget*>( m_maximizeButton));

    m_closeButton = new MenuButton( MenuButton::CloseButton, this);
    m_titleLayout->addWidget( reinterpret_cast<QWidget*>( m_closeButton));
    connect( m_closeButton, &MenuButton::clicked, this, &QMainWindow::close);







}

QLayout *MainWindowFl::customWidgetLayout() const
{
    return m_customWidgetLayout;
}
