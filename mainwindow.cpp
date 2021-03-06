#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createMenu();
    createWidget();
    lf=new LoginFrame();
    lf->show();

    if(DFile().initialDataBase()){

        qDebug() << "here"<<1;
    }
    connect(lf,SIGNAL(login(QString,QString,QString,QString,QString)),this,SLOT(initall(QString,QString,QString,QString,QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
//菜单栏创建(与槽函数连接)其他功能连接也在这进行
//具体控件名字见.ui文件
void MainWindow::createMenu(){
    connect(ui->actionquit, &QAction::triggered, this, &MainWindow::actionExit);
    connect(ui->actionCDatabase,&QAction::triggered,this,&MainWindow::createDatabase);    //新建库
    connect(ui->actionCTable,&QAction::triggered,this,&MainWindow::createTable);    //新建表
    connect(ui->actionODatabase,&QAction::triggered,this,&MainWindow::openDatabase);    //打开库
    connect(ui->actionIField,&QAction::triggered,this,&MainWindow::insertField);    //插入字段
    connect(ui->actionIRecord,&QAction::triggered,this,&MainWindow::insertRecord);    //插入记录
    connect(ui->actionOTable,&QAction::triggered,this,&MainWindow::showRecord);                //打开表
    connect(ui->actionQuery,&QAction::triggered,this,&MainWindow::queryRecord);    //条件查询
//    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(get_row_and_col(int,int)));
    connect(ui->actionDField,&QAction::triggered,this,&MainWindow::deleteField);    //删除字段
    connect(ui->actionUField,&QAction::triggered,this,&MainWindow::updateField);    //修改字段
    connect(ui->actionDDatabase,&QAction::triggered,this,&MainWindow::deleteDatabase);    //删除库
    connect(ui->actionDTable,&QAction::triggered,this,&MainWindow::deleteTable);    //删除表
    connect(ui->actionLog,&QAction::triggered,this,&MainWindow::systemLog);//日志查询
    connect(ui->actionDRecord,&QAction::triggered,this,&MainWindow::deleteRecord);    //删除记录
    connect(ui->actionURecord,&QAction::triggered,this,&MainWindow::updateRecord);    //修改记录
    connect(ui->actionRight,&QAction::triggered,this,&MainWindow::controlRight);      //权限与安全
    connect(ui->actionUserInfo,&QAction::triggered,this,&MainWindow::userInfo);    //查看用户
    connect(ui->actionsql,&QAction::triggered,this,&MainWindow::actionSql);    //导入sql
    connect(ui->actionreload,&QAction::triggered,this,&MainWindow::actionReload);
}


//根据当前用户初始化所有信息
void MainWindow::initall(QString name,QString dba,QString create,QString update,QString dele){
    this->user=name;
    this->dbaright=dba=="1"?true:false;
    this->createright=create=="1"?true:false;
    this->updateright=update=="1"?true:false;
    this->deleright=dele=="1"?true:false;
    qDebug()<<dbaright<<createright<<updateright<<deleright;
    //根据各权限设置功能
    if(createright==false&&dbaright==false){
        ui->actionCDatabase->setEnabled(false);
        ui->actionCTable->setEnabled(false);
    }
    if(updateright==false&&dbaright==false){
        ui->actionUField->setEnabled(false);
        ui->actionURecord->setEnabled(false);
    }
    if(deleright==false&&dbaright==false){
        ui->actionDRecord->setEnabled(false);
        ui->actionDField->setEnabled(false);
        ui->actionDRecord->setEnabled(false);
        ui->actionDDatabase->setEnabled(false);
    }

    //TODO根据user名加载出这个用户已经存在的库、表
    QString dirname="D:/MyDataBase/"+ user;
    QDir dir(dirname);
    QStringList names = dir.entryList(QDir::Dirs);
    names.removeOne(".");
    names.removeOne("..");
    auto it=names.begin();
    while(it!=names.end()){
        QString databasename=*it;
        //qDebug()<<*it<<endl;
        createDatabase();
        databaseItem->setText(0,databasename);
        hasht[databaseItem]=1;

        QString biaodirname="D:/MyDataBase/"+ user+"/"+databasename;
        QDir biaodir(biaodirname);
        QStringList tablenames = biaodir.entryList(QDir::Dirs);
        tablenames.removeOne(".");
        tablenames.removeOne("..");
        auto biaoit=tablenames.begin();
        while(biaoit!=tablenames.end()){
            QString tablename=*biaoit;
            createTable();
            tableItem->setText(0,tablename);
            hasht[tableItem]=1;
            biaoit++;
        }
        it++;
    }
    this->show();
}

//退出按钮槽函数
void MainWindow::actionExit()
{
    this->close();
}

//有条件退出
void MainWindow::closeEvent(QCloseEvent* event)
{
    /*
    event->accept();//接受退出
    event->ignore();//不接受退出
    */
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, QStringLiteral("提示"),QStringLiteral("是否退出程序") ,QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::Yes)
    {
        event->accept();//接受退出
    }
    else
    {
        event->ignore();//不接受退出
    }
}

//创建库标栏、主界面点击响应
void MainWindow::createWidget(){
    //Item点击事件的连接
    connect(ui->treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),this,SLOT(slotDoubleClickItem(QTreeWidgetItem *, int)));
    connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem *,int)),this,SLOT(slotClickItem(QTreeWidgetItem*,int)));
    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(slotClickTableItem(int,int)));
}

/**
 * @brief 新建库槽函数
 */
void MainWindow::createDatabase(){
    QTreeWidgetItem *Ku=new QTreeWidgetItem(ui->treeWidget);
    QIcon icon;
    icon.addPixmap(QPixmap(":/pic/Ku.png"), QIcon::Selected);
    Ku->setIcon(0,icon);

    Ku->setText(0,QStringLiteral("请输入名称"));
    databaseItem=Ku;
}

/**
 * @brief 删除库
 */
void MainWindow::deleteDatabase(){
    if(databaseItem!=NULL){
        QString dirname = "D:/MyDataBase/"+ user+'/' + databasename;
        QDir dir;
        dir.setPath(dirname);
        dir.removeRecursively();

        delete databaseItem;
        ui->tableWidget->setColumnCount(0);
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }else{
        QMessageBox::information(this,QStringLiteral("提示"),QStringLiteral("请先选择库!"));
    }
}

/**
 * @brief 删除表
 */
void MainWindow::deleteTable(){
    if(this->tableItem!=NULL){
        QString dirname = "D:/MyDataBase/"+ user+'/' + databasename+'/'+tablename;
        QDir dir;
        dir.setPath(dirname);
        dir.removeRecursively();

        delete tableItem;
        SQL().deleteT(user,databasename,tablename);
        ui->tableWidget->setColumnCount(0);
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }else{
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("请先选择表!"));
    }

}

//新建表槽函数
void MainWindow::createTable(){
    if(databaseItem!=NULL){
        QTreeWidgetItem *biao=new QTreeWidgetItem();
        databaseItem->addChild(biao);
        QIcon icon;
        icon.addPixmap(QPixmap(":/pic/biao.png"), QIcon::Selected);
        biao->setIcon(0,icon);
        biao->setText(0,QStringLiteral("请输入名称"));
        tableItem=biao;
    }else{
        QMessageBox::information(this,QStringLiteral("提示"),QStringLiteral("请先选择库!"));
    }

}

//插入字段槽函数
void MainWindow::insertField(){
    if(this->tableItem!=NULL){
        td=new TableDesign();
        td->tableItem=this->tableItem;//传递选中的表指针以便存值
        td->databasename=this->databasename;
        td->tablename=this->tablename;
        td->user=this->user;
        td->show();
        showTableWidget();

    }else{
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("请先选择表!"));
    }
}

//插入记录
void MainWindow::insertRecord(){
    if(this->tableItem!=NULL){
        ri=new RecordInsert();
        ri->tableItem=this->tableItem;
        ri->tablename=this->tableItem->text(0);
        ri->databaseItem=this->tableItem->parent();
        ri->databasename=this->tableItem->parent()->text(0);
        ri->user=this->user;
        ri->initTableWidget();
        ri->show();
    }else{
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("请先选择表!"));
    }
}

//删除记录
void MainWindow::deleteRecord(){
    if(recordTable==true){
         SQL().deleteRecord(this->user,this->databasename,this->tablename,this->recordRow);
         TFile().deleteRecord(user,databasename,tablename,recordRow);
    }else{
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("请先选择记录!"));
    }
}

//修改记录
void MainWindow::updateRecord(){
    if(recordTable==true){
        deleteRecord();
        ri=new RecordInsert();
        ri->tableItem=this->tableItem;
        ri->tablename=this->tableItem->text(0);
        ri->databaseItem=this->tableItem->parent();
        ri->databasename=this->tableItem->parent()->text(0);
        ri->user=this->user;
        ri->changeLabel(QStringLiteral("修改记录"));
        ri->initTableWidget();
        ri->show();
    }else{
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("请先选择记录!"));
    }
}

//TreeWidgetItem(库表)双击改名
void MainWindow::slotDoubleClickItem(QTreeWidgetItem *item, int col) {
    doubleClickItem = nullptr;
    if(hasht[item]==1){
        return ;
    }
    if (col == 0) {
        doubleClickItem = item;
        QLineEdit* lineEdit = new QLineEdit(this);
        lineEdit->setText(QStringLiteral("请输入名称"));
        connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(slotFinishEdit()));
        ui->treeWidget->setItemWidget(doubleClickItem, 0, lineEdit);
    }
}

//(库表)改名结束
void MainWindow::slotFinishEdit(){
    if (doubleClickItem != nullptr) {
        QLineEdit *edit = qobject_cast<QLineEdit*>(ui->treeWidget->itemWidget(doubleClickItem, 0));
        if (!edit) {
            return;
        }
        QString text = edit->text();
        ui->treeWidget->removeItemWidget(doubleClickItem, 0);
        if(text==""){
            QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("请输入名称"));

        }else{

            doubleClickItem->setText(0,text);
            //创建库
            if(doubleClickItem==databaseItem)
            {
                databasename=text;
                 //DFile::createDataBase(text,this->user);
                 SQL().CreateD(this->user,databasename);
                 DFile().addRecord(1,user,text);
            }
            //创建表
            if(doubleClickItem==tableItem)
            {
                 tablename=text;
                 //TFile::createTable(this->user,databasename,text);
                 SQL().CreateT(this->user,this->databasename,this->tablename);
                 DFile().addDBRecord(1,this->user,databasename,text);
            }
            QMessageBox::StandardButton button;
            button = QMessageBox::question(this, QStringLiteral("提示"), QStringLiteral("名称无法修改，确定此名？") ,QMessageBox::Yes | QMessageBox::No);


        }
        hasht[doubleClickItem]=1;
    }
}

//单击（选中）库表槽函数
void MainWindow::slotClickItem(QTreeWidgetItem *item,int col){
    QTreeWidgetItem *p=NULL;
    p=item->parent();
    if(p!=NULL){
       tableItem=item;
       databasename=item->parent()->text(0);
       tablename=item->text(0);
      // tablename=tableItem->text(0);
       databaseItem=NULL;
        //如果说单击的这个item不是根节点即不是库，是表那么就显示其设计界面
       showTableWidget();
    }else{
        databaseItem=item;
        tablename="";
        databasename=item->text(0);
        // databasename=databaseItem->text(col);
         tableItem=NULL;
    }
}

//双击选中记录槽函数
void MainWindow::slotClickTableItem(int row,int column){
    //判断当前已打开记录界面而非字段界面
    if(recordTable==true){
        this->recordRow=row;
        qDebug()<<"recordRow"<<recordRow;
    }else
    {
        this->tableRow=row;
        qDebug()<<"tableRow"<<tableRow;
    }
}

//展开库
void MainWindow::openDatabase(){
    if(databaseItem!=NULL){
        databaseItem->setExpanded(1);
    }
}

//显示图表(字段)
void MainWindow::showTableWidget(){
    recordTable=false;
    ui->tableWidget->show();
    //先清空
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //创建表头
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem(QStringLiteral("字段名")));
    ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem(QStringLiteral("字段类型")));
    ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem(QStringLiteral("长度")));
    ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem(QStringLiteral("默认值")));
    ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem(QStringLiteral("最小值")));
    ui->tableWidget->setHorizontalHeaderItem(5,new QTableWidgetItem(QStringLiteral("最大值")));
    ui->tableWidget->setHorizontalHeaderItem(6,new QTableWidgetItem(QStringLiteral("主键")));
    ui->tableWidget->setHorizontalHeaderItem(7,new QTableWidgetItem(QStringLiteral("唯一键")));
    ui->tableWidget->setHorizontalHeaderItem(8,new QTableWidgetItem(QStringLiteral("非空")));
    ui->tableWidget->setHorizontalHeaderItem(9,new QTableWidgetItem(QStringLiteral("注释")));
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//TODO下面读取字段信息

    QString dirname = "D:/MyDataBase/"+ user+'/' + databasename+'/'+tablename;
    QString filename_tdf = dirname + '/' + tablename + ".tdf";
    QFile tdf(filename_tdf);
    tdf.seek(0);
    if(tdf.open(QIODevice::ReadOnly))
    {
qDebug()<<"文件打开成功";
    }
    QDataStream stream (&tdf);

    QString str;
    QStringList strlist;
    int i=0;

    //将值分解后写入单元格
    while(!stream.atEnd()){
qDebug()<<"进入循环了！";
        int RowCont;
        RowCont=ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(RowCont+1);//增加一行
        stream>>str;

        strlist=str.split("|");
        for(int j=0;j<=9;j++)
        {
            if(j==6||j==7||j==8)
            {
                if(strlist[j]=="1")
                {
                    QTableWidgetItem *citem=new QTableWidgetItem();
                    QIcon icon;
                    icon.addPixmap(QPixmap(":/pic/choose.jpg"));
                    citem->setTextAlignment(Qt::AlignCenter);
                    citem->setIcon(icon);
                    ui->tableWidget->setItem(i,j,citem);
                }
            }else
            {
                ui->tableWidget->setItem(i,j,new QTableWidgetItem(strlist[j]));
            }

        }
        i++;
    }
    tdf.close();

}

/**
 * @brief 删除字段
 */
void MainWindow::deleteField(){
    if(this->tableItem!=NULL){

        if(tableRow==-1)
        {
            QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("请先选择要删除的字段!"));
        }
        else
        {
            SQL().deleteField(user,databasename,tablename,ui->tableWidget->item(tableRow,0)->text());
            QString dirname = "D:/MyDataBase/"+ user+'/' + databasename+'/'+tablename;
            //删除记录中该字段
            QString filename_tic = dirname + '/' + tablename + ".tic";
            QFile tic(filename_tic);
            if(tic.open(QIODevice::ReadOnly))
            {
                qDebug()<<"文件打开成功";
            }
            tic.seek(0);
            QDataStream rstream (&tic);
            QString rstr;
            QStringList rstrlist;//放每一条记录
            QStringList pstrlist;//放一条记录里的所有字段

            while(!rstream.atEnd())
            {
                rstream>>rstr;
                pstrlist=rstr.split("|");
                pstrlist.removeAt(tableRow);//删除动作
                rstr=pstrlist.join("|");
                rstrlist.append(rstr);
            }
            tic.close();

            //重新写入
            QFile wtic(filename_tic);
            wtic.open(QFile::WriteOnly|QIODevice::Truncate);//先清空
//            wtic.open(QFile::Append);
            wtic.seek(0);
            QDataStream wstream (&wtic);
            for(int i=0;i<rstrlist.size();i++){
                wstream<<rstrlist[i];
            }
            wtic.close();

            //删除字段
            QString filename_tdf = dirname + '/' + tablename + ".tdf";
            QFile tdf(filename_tdf);
            if(tdf.open(QIODevice::ReadOnly))
            {
        qDebug()<<"文件打开成功";
            }
            tdf.seek(0);
            QDataStream stream (&tdf);
            QString str;
            QStringList strlist;
            int i=0;

            while(!stream.atEnd())
            {
                stream>>str;
                strlist.append(str);
                i++;
            }
            tdf.close();

            //重新写入
            QFile wtdf(filename_tdf);
            wtdf.open(QFile::WriteOnly|QIODevice::Truncate);//先清空
            wtdf.seek(0);
            QDataStream wtdfstream(&wtdf);

            for(i=0;i<strlist.size();i++)
            {
                if(i!=tableRow)       //读到要删除的那一行
                {
                    wtdfstream<<strlist[i];
                }
            }
            wtdf.close();
            tableRow=-1;
            showTableWidget();
        }


    }else{
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("请先选择表!"));
    }
}


/**
 * @brief 修改字段
 */
void MainWindow::updateField(){
    if(this->tableItem!=NULL){
        if(tableRow==-1)
        {
            QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("请先选择要修改的字段!"));
        }else
        {
            QString dirname = "D:/MyDataBase/"+ user+'/' + databasename+'/'+tablename;
            QString filename_tdf = dirname + '/' + tablename + ".tdf";
            QFile tdf(filename_tdf);

            if(tdf.open(QIODevice::ReadOnly))
            {
        qDebug()<<"文件打开成功";
            }
            tdf.seek(0);
            QDataStream stream (&tdf);
            QString str;
            QString str2;
            QString str1;
            QStringList strlist;
            int i=0;

            while(!stream.atEnd())
            {
                stream>>str;
                if(i==tableRow)//读到想要修改的行
                {
qDebug()<<"修改前的str："<<str;
                    str1=str.split("|").at(0);//用于sql语句生成
                    td=new TableDesign();
                    td->tableItem=this->tableItem;//传递选中的表指针以便存值
                    td->databasename=this->databasename;
                    td->tablename=this->tablename;
                    td->user=this->user;
                    td->willModify(str);
                    td->show();
                    int j=0;
                    while(td->modifystr=="")//等待用户点击确定按钮
                    {
                        QCoreApplication::processEvents();
                    }
                    str=td->modifystr;
                    //生成sql
                    SQL().ModifyDesign(user,databasename,tablename,ui->tableWidget->item(tableRow,0)->text(),str);
qDebug()<<"修改后的str："<<str;
                }
                strlist.append(str);
                i++;
            }
            tdf.close();

            //重新写入
            QFile wtdf(filename_tdf);
            wtdf.open(QFile::WriteOnly|QIODevice::Truncate);//先清空
            wtdf.seek(0);
            QDataStream wtdfstream(&wtdf);

            for(i=0;i<strlist.size();i++)
            {
                wtdfstream<<strlist[i];
            }
            wtdf.close();
            tableRow=-1;
            td->modifystr="";
            showTableWidget();
        }
    }else
    {
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("请先选择表!"));
    }
}





//打开表
void MainWindow::showRecord(){
    recordTable=true;
    if(tablename==""){
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("请先选择表!"));
    }
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QString dirname = "D:/MyDataBase/"+ user+'/' + databasename+'/'+tablename;
    QString filename_tdf = dirname + '/' + tablename + ".tdf";
    QFile tdf(filename_tdf);
    tdf.seek(0);
    if(tdf.open(QIODevice::ReadOnly))
    {
        qDebug()<<"文件打开成功";
    }
    QDataStream stream (&tdf);
    QString str;
    QStringList strlist;
    if(stream.atEnd()){
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("该表不存在字段！"));
        this->close();
    }
    int column=0;
    //将值分解后写入单元格
    while(!stream.atEnd()){
        column=ui->tableWidget->columnCount();
        ui->tableWidget->setColumnCount(column+1);
        stream>>str;
        strlist=str.split("|");
        qDebug()<<strlist[0];
        ui->tableWidget->setHorizontalHeaderItem(column,new QTableWidgetItem(strlist[0]));
    }
    tdf.close();

    QString recdir = "D:/MyDataBase/"+ user+'/' + databasename+'/'+tablename;
    QString filename_tic = recdir + '/' + tablename + ".tic";
    QFile tic(filename_tic);
    tic.seek(0);
    if(tic.open(QIODevice::ReadOnly))
    {
        qDebug()<<"文件打开成功";
    }
    QDataStream rstream (&tic);
    QString rstr;
    QStringList rstrlist;
    int m=0;
    //将值分解后写入单元格
    while(!rstream.atEnd()){
        qDebug()<<"进入循环了！";
        int RowCont;
        RowCont=ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(RowCont+1);//增加一行
        rstream>>rstr;
        //qDebug()<<"rstr"<<rstr<<endl;
        rstrlist=rstr.split("|");
        for(int n=0;n<column+1;n++){
            ui->tableWidget->setItem(m,n,new QTableWidgetItem(rstrlist[n]));
        }
        m++;
    }
    tic.close();
}

//条件查询
void MainWindow::queryRecord(){
    QueryFrame *qf=new QueryFrame();
    qf->user=this->user;
    qf->tableItem=this->tableItem;
    qf->databaseItem=this->databaseItem;
    qf->tablename=this->tablename;
    qf->databasename=this->databasename;
    qf->show();
    qf->showWidget();
    connect(qf,SIGNAL(submit(QString)),this,SLOT(forTjc(QString)));
}

//条件查询的配套函数
void MainWindow::forTjc(QString values){
    if(values==""){
        ui->tableWidget->setColumnCount(0);
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        return;
    }
    qDebug()<<values;
    QStringList valueList;
    valueList=values.split("|");//查询的字段及相应信息
    if(tableItem==NULL&&valueList[0]!="sql"){
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("请先选择表！"));
    }
    if(valueList[0]=="sql"){
        databasename=valueList[1];
        tablename=valueList[2];
        //去除表头
        valueList.pop_front();
        valueList.pop_front();
        valueList.pop_front();
    }
    //解析需要获取的字段
    std::vector<int> fields;
    for(int n=0;n<valueList.size();n++){
        QString value=valueList[n];
        std::string svalue=value.toStdString();
        int loc=svalue[0]-'0';//获取需要字段的下标
        fields.push_back(loc);
        qDebug()<<"fields"<<loc;
    }

    //载入字段表头
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QString dirname = "D:/MyDataBase/"+ user+'/' + databasename+'/'+tablename;
    QString filename_tdf = dirname + '/' + tablename + ".tdf";
    QFile tdf(filename_tdf);
    tdf.seek(0);
    if(tdf.open(QIODevice::ReadOnly))
    {
        qDebug()<<"文件打开成功";
    }
    QDataStream stream (&tdf);
    QString str;
    QStringList strlist;
    if(stream.atEnd()){
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("该表不存在字段！"));
        this->close();
    }
    int column=0;
    int p=0;
    int q=0;
    //将查询需要的字段分解后写入单元格
    while(!stream.atEnd()){

        stream>>str;
        strlist=str.split("|");
        if(p<fields.size()&&fields[p]==q){
            column=ui->tableWidget->columnCount();
            ui->tableWidget->setColumnCount(column+1);
            ui->tableWidget->setHorizontalHeaderItem(column,new QTableWidgetItem(strlist[0]));
            p++;
        }
        q++;
    }
    tdf.close();


    //将记录写入表
    QString rdirname = "D:/MyDataBase/"+ user+'/' + databasename+'/'+tablename;
    QString filename_tic = rdirname + '/' + tablename + ".tic";
    QFile tic(filename_tic);
    tic.seek(0);
    if(tic.open(QIODevice::ReadOnly))
    {
        qDebug()<<"文件打开成功";
    }
    QDataStream rstream (&tic);
    if(rstream.atEnd()){
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("该表不存在记录！"));
    }
    while(!rstream.atEnd()){
        QString records;
        QStringList recordList;
        rstream>>records;
        recordList=records.split("|");
        int i=0;
        for(i=0;i<fields.size();i++){
            QString value=valueList[i];
            std::string svalue=value.toStdString();
            int loc=fields[i];//获取记录对应字段下标
            svalue=svalue.substr(1);
            //如果当前字段是*即无查询条件continue
            if(svalue=="*"){
                continue;
            }
            //首先判断是不是范围查询
            int index=svalue.find(",");
            //不是范围查询
            if(index==-1){
                //判断有无！即是否取等于还是不等于
                int index_not=svalue.find("!");
                //取等于的情况
                if(index_not==-1){
                    QString record=recordList[loc];
                    std::string srecord=record.toStdString();
                    if(svalue!=srecord){
                        break;
                    }
                }
                //取不等于的情况
                if(index_not==0){
                    svalue=svalue.substr(1);
                    QString record=recordList[loc];
                    std::string srecord=record.toStdString();
                    if(svalue==srecord){
                        break;
                    }
                }
            }
            //是范围查询
            else{
                std::string mins=svalue.substr(0,index);
                std::string maxs=svalue.substr(index+1);
                QString record=recordList[loc];
                std::string srecord=record.toStdString();
                double nrecord=std::stof(srecord);
                //判断是否符合范围区间
                if(mins!=""){
                    double minn=std::stof(mins);
                    if(nrecord<minn){
                        break;
                    }
                }
                if(maxs!=""){
                    double maxn=std::stof(maxs);
                    if(nrecord>maxn){
                        break;
                    }
                }
            }
        }
        //找到记录
        p=0;
        q=0;
        if(i==valueList.size()){
            int row=ui->tableWidget->rowCount();
            ui->tableWidget->setRowCount(row+1);
            while(p<fields.size()){
                ui->tableWidget->setItem(row,p,new QTableWidgetItem(recordList[fields[p]]));
                p++;
            }
        }
    }
    tic.close();

}

//日志查询
void MainWindow::systemLog()
{
   blogFrame* blog = new blogFrame();
   blog->setUser(this->user);
   int topcount = ui->treeWidget->topLevelItemCount();
   for(int i=0; i<topcount;i++){
       QTreeWidgetItem * clone = ui->treeWidget->topLevelItem(i)->clone();
       blog->addItem(clone);
   }
   blog->show();
   qDebug()<<2;
}

//权限与安全
void MainWindow::controlRight(){
    if(dbaright==false){
        QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("不是管理员无法设置权限!"));
    }else{
        RightFrame *rf=new RightFrame();
        rf->initWidget();
        rf->user=user;
        rf->show();
        connect(rf,SIGNAL(change(bool,bool,bool,bool)),this,SLOT(changeRight(bool,bool,bool,bool)));

    }
}

//修改当前用户的权限（并非在文件中修改）
void MainWindow::changeRight(bool dba,bool create,bool update,bool dele){
    dbaright=dba;
    createright=create;
    updateright=update;
    deleright=dele;
    //根据各权限设置功能
    if(createright==false&&dbaright==false){
        ui->actionCDatabase->setEnabled(false);
        ui->actionCTable->setEnabled(false);
    }
    if(updateright==false&&dbaright==false){
        ui->actionUField->setEnabled(false);
        ui->actionURecord->setEnabled(false);
    }
    if(deleright==false&&dbaright==false){
        ui->actionDRecord->setEnabled(false);
        ui->actionDField->setEnabled(false);
        ui->actionDRecord->setEnabled(false);
        ui->actionDDatabase->setEnabled(false);
    }

}

//查看当前用户的权限
void MainWindow::userInfo(){
    std::string str;
    str+="当前用户名:"+user.toStdString()+"\n";
    str+="所有权限:";
    if(dbaright==true){
        str+="管理员 ";
    }
    if(createright){
        str+=" 创建权限";
    }
    if(updateright){
        str+=" 创建权限";
    }
    if(deleright){
        str+=" 创建权限";
    }
    QMessageBox::information(this, QStringLiteral("用户信息"),QString::fromLocal8Bit(str.c_str()));
}

//sql导入
void MainWindow::actionSql(){
    SqlInput *si=new SqlInput();
    si->user=user;
    si->show();

    //查询的信号
    connect(si,SIGNAL(query(QString)),this,SLOT(forTjc(QString)));
}

//重新加载
void MainWindow::actionReload(){
    ui->treeWidget->clear();
    QString dirname="D:/MyDataBase/"+ user;
    QDir dir(dirname);
    QStringList names = dir.entryList(QDir::Dirs);
    names.removeOne(".");
    names.removeOne("..");
    auto it=names.begin();
    while(it!=names.end()){
        QString databasename=*it;
        //qDebug()<<*it<<endl;
        createDatabase();
        databaseItem->setText(0,databasename);
        hasht[databaseItem]=1;

        QString biaodirname="D:/MyDataBase/"+ user+"/"+databasename;
        QDir biaodir(biaodirname);
        QStringList tablenames = biaodir.entryList(QDir::Dirs);
        tablenames.removeOne(".");
        tablenames.removeOne("..");
        auto biaoit=tablenames.begin();
        while(biaoit!=tablenames.end()){
            QString tablename=*biaoit;
            createTable();
            tableItem->setText(0,tablename);
            hasht[tableItem]=1;
            biaoit++;
        }
        it++;
    }
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
