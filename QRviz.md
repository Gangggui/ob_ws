
### Brief


#### 代码
```c++
class QRviz:public QThread  
{  
    Q_OBJECT  
public:  
    QRviz(QVBoxLayout *layout,QString node_name);  
    ~QRviz();  
      
//    QList<rviz::Display *> rvizDisplays_;  
    void DisplayInit(QString ClassID, bool enabled, QMap<QString, QVariant> namevalue);  
    void DisplayInit(QString ClassID, QString name, bool enabled, QMap<QString, QVariant> namevalue);  
      
    void RemoveDisplay(QString name);  
    void RemoveDisplay(QString ClassID, QString name);  
      
    void RenameDisplay(QString oldname, QString newname);  
      
    void OutDisplaySet(QString path);  
    void ReadDisplaySet(QString path);  
      
    void run();  
    void createDisplay(QString display_name,QString topic_name);  
    //设置全局显示属性  
    void SetGlobalOptions(QString frame_name,QColor backColor,int frame_rate);  
  
    void Set_Pos();  
    void Set_Goal();  
    void Set_MoveCamera();  
    void Set_Select();  
    //发布goal话题的坐标  
    void Send_Goal_topic();  
      
    void GetDisplayTreeModel();  
      
signals:  
    void ReturnModelSignal(QAbstractItemModel *model);  
      
private:  
    int GetDisplayNum(QString ClassID);  
    int GetDisplayNum(QString ClassID, QString name);  
    int GetDisplayNumName(QString name);  
      
    //rviz显示容器  
    rviz::RenderPanel *render_panel_;  
    rviz::VisualizationManager *manager_;  
  
    rviz::DisplayGroup *display_group_;  
  
    //rviz工具  
    rviz::Tool *current_tool;  
    //rviz工具控制器  
    rviz::ToolManager *tool_manager_;  
    QVBoxLayout *layout;  
    QString nodename;  
      
    QMap<QString, QVariant> nullmap;  
private slots:  
    void addTool( rviz::Tool* );  
  
 //   rviz::VisualizationManager *manager_=NULL;  
//    rviz::RenderPanel *render_panel_;  
  
};
```