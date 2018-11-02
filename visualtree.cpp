#include "visualtree.h"
#include "ui_visualtree.h"
#include <iostream>
#include <QString>
#include "tree.h"
#include <QPainter>
#include <QPoint>
#include <string>


int Tree::Node::left_nodes = 0;
int Tree::Node::right_nodes = 0;

VisualTree::VisualTree(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VisualTree)
    {
        ui->setupUi(this);
    }

VisualTree::~VisualTree()
{
    delete _node;
    delete ui;
}

void VisualTree::on_insert_button_clicked()
{
    QString raw_data = ui->Input_text->text();
    ui->Input_text->setText("");

    if(raw_data.contains(",")){
        _node->ResetLastLabel();
        QStringList split_data = raw_data.split(",");

        for(const auto &a : split_data){
            Tree::Data _data;
            _data.val = a.toInt();
            _node->Insert(_data);

            ui->largest_num->setText(QString::number(_node->GetLargestNumber()));
            ui->smllest_num->setText(QString::number(_node->GetSmallestNumber()));
            ui->left_branch->setText(QString::number(Tree::Node::left_nodes));
            ui->right_branch->setText(QString::number(Tree::Node::right_nodes));
        }
    }
    else{
        Tree::Data _data;
        _data.val = raw_data.toInt();
        if(!(_node->Contain(raw_data.toInt()))){
            _node->ResetLastLabel();
            _node->Insert(_data);

            ui->largest_num->setText(QString::number(_node->GetLargestNumber()));
            ui->smllest_num->setText(QString::number(_node->GetSmallestNumber()));
            ui->left_branch->setText(QString::number(Tree::Node::left_nodes));
            ui->right_branch->setText(QString::number(Tree::Node::right_nodes));
        }
    }

    if(_node->IsSymetrical()==1){
        ui->symetrcal_lab->setText("Yes");
    }
    else{
       ui->symetrcal_lab->setText("No");
    }

    DrawTree = true;
    update();
}

void VisualTree::on_Root_set_clicked()
{
    int root = ui->Root_inp->text().toInt();

    Tree::Data r_data;
    r_data.val = root;

    _node = new Tree::Node(r_data);

    ui->Root_inp->setEnabled(false);
    ui->Root_set->setEnabled(false);
}

void VisualTree::paintEvent(QPaintEvent *event){
    if(DrawTree == true){
        QPainter paint_node(this);
        paint_node.setPen(QPen(Qt::black,2));
        std::vector<Tree::Data> nodes_data = _node->SetPositionOfNodesForVisualization();

        const int size = _node->DrawingSize/2;
        QPoint line_pos;
        line_pos.setX(_node->start_pos.x()+size);
        line_pos.setY(_node->start_pos.y()+size);
        std::vector<QPoint> nodes_lines = _node->GetVectorOfLinesBetwenNodes();
        for(const auto& a : nodes_lines){
            paint_node.drawLine(line_pos.x(),line_pos.y(),a.x()+size,a.y()+size);
            line_pos.setX(a.x()+size);
            line_pos.setY(a.y()+size);
        }

        paint_node.setBrush(QBrush(QColor(Qt::green)));
        for(const auto& a : nodes_data){
            QPoint node_pos(a.posX,a.posY);

            if(a.new_node == false){
                paint_node.drawEllipse(a.posX,a.posY,_node->DrawingSize,_node->DrawingSize);
            }
            else{
                paint_node.setBrush(QBrush(QColor(Qt::red)));
                paint_node.drawEllipse(a.posX,a.posY,_node->DrawingSize,_node->DrawingSize);
                paint_node.setBrush(QBrush(QColor(Qt::green)));
            }

            paint_node.drawText(QRectF(QPointF(node_pos),QSizeF(QSize(34,31))),QString::number(a.val),QTextOption(Qt::AlignCenter));
        }
    }
}
