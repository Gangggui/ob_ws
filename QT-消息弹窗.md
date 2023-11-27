## 1. 标准信息提示框

    information：标准信息提示框

QMessageBox::warning(this,"Title","Error Message");
    QMessageBox::information(NULL,  "Title",  "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    //QMessageBox ::Yes, QMessageBox :: No, QMessageBox :: Retry , QMessageBox :: Ignore , QMessageBox :: Ok , QMessageBox :: Cancel    //可选

![](https://img-blog.csdnimg.cn/20210406133815748.png)

![](https://img-blog.csdnimg.cn/20210406133844957.png)

switch(QMessageBox::information(this,"Warning",tr("Save changes to document?"),
        QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel,QMessageBox::Save))
    {
    case QMessageBox::Save:
        qDebug() << " Warning button / Save " << endl;;
        break;
    case QMessageBox::Discard:
        qDebug() << " Warning button / Discard " << endl;;
        break;
    case QMessageBox::Cancel:
        qDebug() << " Warning button / Cancel " << endl;;
        break;
    default:
        break;
    }

- 第一个参数是父控件指针
- 第二个参数是标题
- 第三个参数是内容
- 第四个参数是窗口里面要多少个按钮（默认为 OK）
- 第五个参数指定按下 Enter 时使用的按钮。（默认为 NoButton，此时 QMessageBox 会自动选择合适的默认值。）

## 2. 判断提示框按钮

//ico弹窗
    QMessageBox::critical(this,"Critical",tr("tell user a critical error"));              //错误
    //QMessageBox::warning 警告 QMessageBox::critical 错误 QMessageBox::Information 叹号 QMessageBox::Question 问号

![](https://img-blog.csdnimg.cn/20210406134428868.png)

![](https://img-blog.csdnimg.cn/20210406134442927.png)

## 3. 提示框自带图标

//自定义ico
    QMessageBox customMsgBox;
    customMsgBox.setWindowTitle("Custom message box");
    QPushButton *lockButton = customMsgBox.addButton(tr("Lock"),QMessageBox::ActionRole);
    QPushButton *unlockButton = customMsgBox.addButton(tr("Unlock"),QMessageBox::ActionRole);
    QPushButton *cancelButton = customMsgBox.addButton(QMessageBox::Cancel);
    customMsgBox.setIconPixmap(QPixmap("D:/ico.ico"));//可以设置png图形
    customMsgBox.setText(tr("This is a custom message box"));
    customMsgBox.exec();
 
    if(customMsgBox.clickedButton() == lockButton)
        qDebug() << " Custom MessageBox / Lock ";
    if(customMsgBox.clickedButton() == unlockButton)
        qDebug() << " Custom MessageBox / Unlock ";
    if(customMsgBox.clickedButton() == cancelButton)
        qDebug() << " Custom MessageBox / Cancel ";

QMessageBox *box = new QMessageBox(QMessageBox::Information,"Title","Content");
    QTimer::singleShot(1500,box,SLOT(accept())); //也可将accept改为close
    box->exec();//box->show();都可以

![](https://img-blog.csdnimg.cn/20210406141113946.png)

![](https://img-blog.csdnimg.cn/2021040614115423.png)

![](https://img-blog.csdnimg.cn/20210406141205349.png)

## 4. 定时关闭提示框

QMessageBox *box = new QMessageBox(QMessageBox::Information,"Title","Content");
    QTimer::singleShot(1500,box,SLOT(accept())); //也可将accept改为close
    box->exec();//box->show();都可以