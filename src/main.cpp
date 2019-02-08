#include<QApplication>
#include<QTextEdit>
#include<QTextStream>
#include<QFile>
#include<QObject>
#include<QDebug>

// https://stackoverflow.com/a/34238144
class FocusWatcher : public QObject
{
   Q_OBJECT
public:
   explicit FocusWatcher(QObject* parent = nullptr) : QObject(parent)
   {
      if (parent)
         parent->installEventFilter(this);
   }
   virtual bool eventFilter(QObject *obj, QEvent *event) override
   {
      Q_UNUSED(obj)
      if (event->type() == QEvent::FocusOut)
         emit focusChanged(false);

      return false;
   }

Q_SIGNALS:
   void focusChanged(bool in);
};

class MyNote : public QTextEdit
{
    Q_OBJECT
public:
    MyNote(QString filename, QWidget *parent = nullptr) : QTextEdit(parent), filename(filename)
    {
        textEdit.setFontFamily("Noto Mono");
        textEdit.setFontPointSize(12);
        textEdit.setText(getFileContents(filename));
        textEdit.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        QObject::connect(new FocusWatcher(&textEdit), &FocusWatcher::focusChanged, this, &MyNote::onFocusLoss);
        QObject::connect(&textEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));

        textChanged = false;
        
        textEdit.show();
    }
private:
    QString getFileContents(QString filename)
    {
        QFile file(filename);
        if(!file.open(QFile::ReadOnly | QFile::Text))
        {
            qDebug() << "Could not open file" << filename << "for reading";
            exit(1);
        }

        QTextStream textStream(&file);
        QString retVal = textStream.readAll();
        file.close();

        qDebug() << "File" << filename << "read";
        return retVal;
    }

    void setFileContents(QString filename, QString contents)
    {
        QFile file(filename);
        
        // truncate flag is needed for file overwriting 
        if(!file.open(QFile::ReadWrite | QFile::Truncate | QFile::Text))
        {
            qDebug() << "Could not open file" << filename << "for writing";
            exit(1);
        }

        QTextStream textStream(&file);
        textStream << contents;
        textStream.flush();
        file.close();

        qDebug() << "File" << filename << "written";
    }

    void onFocusLoss()
    {
        if(!textChanged)
            return;
    
        setFileContents(filename, textEdit.toPlainText());
        textChanged = false;
    }

private slots:
    void onTextChanged()
    {
        textChanged = true;
    }

private:
    QTextEdit textEdit;
    QString filename;
    bool textChanged;
};

void printUsageAndExit(char *argv0)
{
    qDebug() << "USAGE:" << argv0 << "<filename>";
    exit(0);
}

int main(int argc, char **argv)
{
    if(argc != 2)
        printUsageAndExit(argv[0]);

    QApplication app(argc, argv);
    
    MyNote note(argv[1]);
    
    return app.exec();
}

#include "main.moc"
