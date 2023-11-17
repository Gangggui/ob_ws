#qt

>https://blog.csdn.net/gongjianbo1992/article/details/108612138

#### Brief
QAbstractTableModel 继承自 QAbstractItemModel，主要用于为 QTableView 提供相关接口

#### 展示表格数据
继承 QAbstractTableModel 后，至少要实现三个纯虚函数接口才能进行实例化：
```c++
// 直接返回展示表格的行列，参数忽略;parent 参数主要是给树形列表用的
virtual int rowCount(const QModelIndex &parent = QModelIndex()) const = 0;
virtual int columnCount(const QModelIndex &parent = QModelIndex()) const = 0;

// QModelIndex 模型索引，提供了对信息的临时引用，可用于通过模型检索或修改数据，一般情况下我们只需要取他附带的行列值即可。
// 获取数据的类型是通过 role 角色参数来区分的，这是一个 Qt::ItemDataRole 枚举
virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const = 0;
```

#### Demo
```c++
#include <QAbstractTableModel>
 
class MyTableModel : public QAbstractTableModel
{
    Q_OBJECT
    struct ModelItem
    {
        QString name;
        int sex;
        int age;
        int score;
    };
 
public:
    explicit MyTableModel(QObject *parent = nullptr)
        : QAbstractTableModel(parent)
    {
        modelData=QList<ModelItem>{
        {"aa",1,20,90},
        {"bb",1,23,91},
        {"cc",0,21,95},
    };
    }
 
    //获取行数
    int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        return modelData.count();
    }
    //获取列数
    int columnCount(const QModelIndex &parent = QModelIndex()) const override
    {
        return 4;
    }
    //获取单元格数据
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {
        if(!index.isValid())
            return QVariant();
        if(role == Qt::DisplayRole || role == Qt::EditRole)
        {
            const int row=index.row();
            switch(index.column())
            {
            case 0: return modelData.at(row).name;
            case 1: return (modelData.at(row).sex==0)?"woman":"man";
            case 2:return modelData.at(row).age;
            case 3:return modelData.at(row).score;
            }
        }
        return QVariant();
    }
 
private:
    //数据
    QList<ModelItem> modelData;
};
```
然后使用 view 的 setModel 接口将 new 出来的 model 实例设置给 view：

    MyTableModel *model=new MyTableModel(ui->tableView);
    ui->tableView->setModel(model);
显示如下：
![[Pasted image 20231117215349.png]]

#### 单元格启用编辑
如果使用通用的编辑功能（通过 view 的 editTriggers 设置触发编辑状态的方式，一般为双击），model 需要实现两个接口：
```c++
//设置单元格数据
bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole) override;
//单元格的可操作性标志位，如可编辑，可选中等
Qt::ItemFlags flags(const QModelIndex& index) const override;
```
当我们双击单元格，允许编辑的单元格会创建一个编辑组件（这是由 delegate 完成的），我们修改数据后回车或切换焦点完成编辑，编辑好的数据会通过 setData 接口设置给 model。setData 接口参数含义和 data 差不多，只是有一个设置成功或失败的返回值
```c++
bool MyTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        const int row = index.row();
        switch(index.column())
        {
        case 0: modelData[row].name = value.toString(); break;
        case 1: modelData[row].sex = (value.toString() == "man")?1:0; break;
        case 2: modelData[row].age = value.toInt(); break;
        case 3: modelData[row].score = value.toInt(); break;
        }
        //发送信号触发刷新
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}
 
Qt::ItemFlags MyTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
}
```

#### 表头
>https://gongjianbo1992.blog.csdn.net/article/details/108655432

一个完整的 QTableView 还包含了行列两个 QHeaderView 表头，表头的 model 可以独立设置，但是一般用 tablemodel 的相关接口提供数据就行了
```c++
//获取表头数据,默认实现直接返回的行列号
QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
//设置表头数据
bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;
```
重载自定义实现:
```c++
void MyTableModel::setHorHeaderData(const QList<QString> &headers)
{
    //自定义的表头设置接口，horHeaderData为QList<QString>成员变量
    horHeaderData=headers;
    emit headerDataChanged(Qt::Horizontal, 0, headers.count()-1);
}
 
 
QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    //注意，如果用了sortproxymodel，这个section是实际数据的index，不是界面看到的index
    //区分横表头和竖表头
    if(orientation == Qt::Horizontal){
        //这里我们只设置居中对齐和文本
        if (role == Qt::DisplayRole){
            //这里把横项列表头的文本设计为可以设置的
            if(section>=0 && section<horHeaderData.count())
                return horHeaderData.at(section);
            return QString("Col %1").arg(section + 1);
        }else if(role == Qt::TextAlignmentRole){
            return Qt::AlignCenter;
        }
    }else{
        if (role == Qt::DisplayRole)
            return QString("Row %1").arg(section + 1);
        else if(role == Qt::TextAlignmentRole)
            return Qt::AlignCenter;
    }
    return QVariant();
}
 
bool MyTableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    //设计为横项列表头可以设置
    if (orientation == Qt::Horizontal && section>=0 && section<horHeaderData.count()) {
        horHeaderData[section] = value.toString();
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}
```

常用设置项:
```c++
    //表头实例
    QHeaderView *header=table->horizontalHeader();
    //拖拽交换行
    header->setSectionsMovable(true);
    //如何决策宽高
    header->setSectionResizeMode(QHeaderView::Fixed);
    //是否可以点击
    header->setSectionsClickable(false);
    //选中时高亮
    header->setHighlightSections(false);
    //默认宽高，放到table设置宽高的接口前，不然被覆盖
    header->setDefaultSectionSize(100);
    //最后一列填充
    header->setStretchLastSection(true);
 
    //排序
    table->setSortingEnabled(true);
    //设置第三列列宽
    //table->setColumnWidth(2,200);
```

#### 排序
QTableView 有个 setSortingEnabled 接口，设置为 true 后，我们就可以通过点击表头根据某一列的数据进行排序，支持升序和降序。
1. 第一是使用 QSortFilterProxyModel ，该接口提供了排序的默认实现，如果要自定义排序规则可以重新实现其 lessThan 接口。使用它的好处是 reset model 数据后排序依然有效。不方便的是他的排序只是改变了单元格的显示位置索引，数据其实是没有修改顺序的，这就导致排序后行号就还是原来的行号。
2. 第二是自定义实现 model 的 sort 接口。好处是排序后直接修改的原始数据，行号是正常的升序。坏处是 reset model 后不会自动排序，需要做信号槽的关联来完成，或者加载数据时处理下；而且修改了原始数据就不能恢复未排序的状态了，我们想要恢复还得在初始加载数据的时候保留这个索引在每一行的数据里，这样在恢复默认顺序的时候根据这个索引排序。
```c++
    QTableView *table=ui->tableView;
    model=new MyTableModel(ui->tableView);
    //想要利用view支持的点击表头排序功能
    //我们可以用QSortFilterProxyModel完成排序，或者实现model的sort接口来完成排序
    //其次，view要设置setSortingEnabled为true，且表头是可点击的
#if 0
    //借助QSortFilterProxyModel
    QSortFilterProxyModel *proxy=new QSortFilterProxyModel(ui->tableView);
    proxy->setSourceModel(model);
    table->setModel(proxy);
#else
    //借助model的sort接口，基类实现不执行任何操作，要自己实现
    table->setModel(model);
#endif
```

sort排序
```c++
void MyTableModel::sort(int column, Qt::SortOrder order)
{
    if(modelData.isEmpty()||column<0||column>=columnCount())
        return;
    //判断升序降序
    const bool is_asc = (order == Qt::AscendingOrder);
    //排序
    std::sort(modelData.begin(), modelData.end(),
              [column, is_asc, this](const MyModelItem &left,const MyModelItem &right){
        //我用QVariant只是在以前的基础上改的，自定义类型可以不用这个
        //这里假设单元格数据都是任意类型的
        const QVariant left_val = left.at(column);
        const QVariant right_val = right.at(column);
 
        //辅助接口，a<b返回true
        return is_asc
                ?lessThan(left_val,right_val)
               :lessThan(right_val,left_val);
    });
    //更新view
    dataChanged(index(0,0),index(modelData.count()-1,columnCount()-1));
}
 
bool MyTableModel::lessThan(const QVariant &left, const QVariant &right) const
{
    //参照QAbstractItemModelPrivate::isVariantLessThan的实现
    //这些都是通用型的排序规则，一般我们会有自定义的需求，比如根据字符串中的数字排序
    //有些类型需要包含头文件才能使用，如datetime
    if (left.userType() == QMetaType::UnknownType)
        return false;
    if (right.userType() == QMetaType::UnknownType)
        return true;
    switch (left.userType()) {
    case QMetaType::Int:
        return left.toInt() < right.toInt();
    case QMetaType::UInt:
        return left.toUInt() < right.toUInt();
    case QMetaType::LongLong:
        return left.toLongLong() < right.toLongLong();
    case QMetaType::ULongLong:
        return left.toULongLong() < right.toULongLong();
    case QMetaType::Float:
        return left.toFloat() < right.toFloat();
    case QMetaType::Double:
        return left.toDouble() < right.toDouble();
    case QMetaType::QChar:
        return left.toChar() < right.toChar();
    case QMetaType::QDate:
        return left.toDate() < right.toDate();
    case QMetaType::QTime:
        return left.toTime() < right.toTime();
    case QMetaType::QDateTime:
        return left.toDateTime() < right.toDateTime();
    case QMetaType::QString: break;
    default: break;
    }
    //Locale表示支持本地字符串
    //if (isLocaleAware)
    return left.toString().localeAwareCompare(right.toString()) < 0;
    //else
    //   return left.toString().compare(right.toString(), cs) < 0;
}
```


#### 加载数据并刷新
当我们想重置 model 的数据时，可以定义一个成员函数，然后将重置的逻辑放在 beginResetModel 和 endResetModel 两个函数调用之间，这样 model 就能正常的刷新数据。调用 beginResetModel 之后，将触发modelAboutToBeReset信号，而 endResetModel 会触发 modelReset 信号
```c++
void MyTableModel::setModelData(const QList<MyModelItem> &datas)
{
    //重置model数据之前调用beginResetModel，此时会触发modelAboutToBeReset信号
    beginResetModel();
    //重置model中的数据
    modelData=datas;
    //数据设置结束后调用endResetModel，此时会触发modelReset信号
    endResetModel();  
    //注意：reset model后，选中的item会失效，我们可以自己写保存和恢复选中项的逻辑
}
```

如果表的行列数是固定的，只是数据变更了，我们可以用 dataChanged 信号来请求刷新。
```c++
    //重置model中的数据，此时行列数一致
    modelData=datas;
    //如果表的行列数是固定的，只是数据变更了，我们可以用 dataChanged 信号来请求刷新。
    emit dataChanged(index(0,0),index(RowMax-1,ColMax-1),QVector<int>());
```
#### 行列动态增删
增删行相关接口（虚函数是我们需要实现的，增删单行的其实也是回调增删多行的接口）：

```cpp
//插入相关接口
bool insertColumn(int column, const QModelIndex &parent = QModelIndex())
virtual bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex())
bool insertRow(int row, const QModelIndex &parent = QModelIndex())
virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex())
//删除相关接口
bool removeColumn(int column, const QModelIndex &parent = QModelIndex())
virtual bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex())
bool removeRow(int row, const QModelIndex &parent = QModelIndex())
virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex())
```

类似 resetModel ，增删行的逻辑也要放在 beginXX 和 endXXX 的调用之间：

```C++
bool MyTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    //row为0就是开始，为rowcount就在尾巴
    if(row<0||count<1||row>rowCount())
        return false;
    //需要将操作放到beginInsertRows和endInsertRows两个函数调用之间
    beginInsertRows(parent, row, row + count - 1);
    for(int i=row;i<row+count;i++)
    {
        //在接口对应行插入空数据
        modelData.insert(i,MyModelItem());
    }
    endInsertRows();
    return true;
}
 
bool MyTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(row<0||count<1||row+count>rowCount())
        return false;
    //需要将操作放到beginRemoveRows和endRemoveRows两个函数调用之间
    beginRemoveRows(parent, row, row + count - 1);
    for(int i=row+count-1;i>=row;i--)
    {
        //移除该行数据
        modelData.removeAt(i);
    }
    endRemoveRows();
    return true;
}
```

### 代码实例

```c++
const QVector<QString> TABLE_HEADER = {  
        "ID",  
        //        "名称",  
        "描述",  
        "类型",  
        "编号",  
};

QVariant TaskModel::headerData(int section, Qt::Orientation orientation, int role) const  
{  
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {  
        return TABLE_HEADER[section];  
    }  
    return QAbstractTableModel::headerData(section, orientation, role);  
}


```