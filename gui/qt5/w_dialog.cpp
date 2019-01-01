/***************************************************************************
    begin       : Mon Feb 15 2010
    copyright   : (C) 2010 by Martin Preuss
    email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/


class Qt5_W_Dialog: public Qt5_W_Widget {
public:
  Qt5_W_Dialog(GWEN_WIDGET *w):Qt5_W_Widget(w) {
  }



  ~Qt5_W_Dialog() {
  }



  virtual int setup() {
    QWidget *qw;
    uint32_t flags;
    GWEN_WIDGET *wParent;
    QLayout *qLayout;
    QSizePolicy::Policy hpolicy=QSizePolicy::Minimum;
    QSizePolicy::Policy vpolicy=QSizePolicy::Minimum;

    flags=GWEN_Widget_GetFlags(_widget);
    wParent=GWEN_Widget_Tree_GetParent(_widget);

    qw=new QT5_DialogBox(dynamic_cast<QT5_GuiDialog*>(getDialog()), QApplication::activeModalWidget());
    qLayout=new QVBoxLayout(qw);

    /* handle flags */
    if (flags & GWEN_WIDGET_FLAGS_FILLX)
      hpolicy=QSizePolicy::Expanding;
    if (flags & GWEN_WIDGET_FLAGS_FILLY)
      vpolicy=QSizePolicy::Expanding;
    qw->setSizePolicy(hpolicy, vpolicy);


    GWEN_Widget_SetImplData(_widget, QT5_DIALOG_WIDGET_REAL, (void*) qw);
    GWEN_Widget_SetImplData(_widget, QT5_DIALOG_WIDGET_LAYOUT, (void*) qLayout);

    if (wParent)
      GWEN_Widget_AddChildGuiWidget(wParent, _widget);
    return 0;
  }



  int addChildGuiWidget(GWEN_WIDGET *wChild) {
    QWidget *qw;
    QBoxLayout *qLayout;
    QWidget *qChild;

    qw=(QT5_DialogBox*) GWEN_Widget_GetImplData(_widget, QT5_DIALOG_WIDGET_REAL);
    assert(qw);

    qLayout=(QBoxLayout*) GWEN_Widget_GetImplData(_widget, QT5_DIALOG_WIDGET_LAYOUT);
    assert(qLayout);

    qChild=getQWidget(wChild);
    assert(qChild);

    qChild->setParent(qw);
    qLayout->addWidget(qChild);

    return 0;
  }



  int setCharProperty(GWEN_DIALOG_PROPERTY prop,
                      GWEN_UNUSED int index,
                      const char *value,
                      GWEN_UNUSED int doSignal) {
    QWidget *qw;

    qw=(QWidget*) GWEN_Widget_GetImplData(_widget, QT5_DIALOG_WIDGET_REAL);
    assert(qw);

    switch(prop) {
    case GWEN_DialogProperty_Title:
      qw->setWindowTitle(QString::fromUtf8(value));
      return 0;
    default:
      break;
    }

    DBG_WARN(GWEN_LOGDOMAIN,
             "Function is not appropriate for this type of widget (%s)",
             GWEN_Widget_Type_toString(GWEN_Widget_GetType(_widget)));
    return GWEN_ERROR_INVALID;
  };



  const char *getCharProperty(GWEN_DIALOG_PROPERTY prop,
                              GWEN_UNUSED int index,
                              const char *defaultValue) {
    QWidget *qw;
    QString str;

    qw=(QWidget*) GWEN_Widget_GetImplData(_widget, QT5_DIALOG_WIDGET_REAL);
    assert(qw);

    switch(prop) {
    case GWEN_DialogProperty_Title:
      str=qw->windowTitle();
      if (str.isEmpty())
        return defaultValue;
      else {
        GWEN_Widget_SetText(_widget, QT5_DIALOG_STRING_TITLE, str.toUtf8());
        return GWEN_Widget_GetText(_widget, QT5_DIALOG_STRING_TITLE);
      }
      break;

    default:
      break;
    }

    DBG_WARN(GWEN_LOGDOMAIN,
             "Function is not appropriate for this type of widget (%s)",
             GWEN_Widget_Type_toString(GWEN_Widget_GetType(_widget)));
    return defaultValue;
  };

};







