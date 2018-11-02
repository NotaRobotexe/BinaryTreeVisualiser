#include "tree.h"
#include <iostream>
#include <vector>
#include <QPoint>

namespace Tree {

	Node::Node(Data NewData) {
		_data = NewData;
	}

	Node::~Node() {
		delete _left;
		delete _right;
	}

	bool Node::IsSymetrical() {
        std::vector <int> left_side;
        std::vector <int> right_side;
		_left->SymetricalChecking(left_side);
		_right->SymetricalChecking(right_side);

		if (left_side.size() != right_side.size())
		{
			return false;
		}
		
		for (size_t i = 0; i < left_side.size(); i++)
		{
			if (left_side[i] != right_side[i])
			{
				return false;
			}
		}

		return true;

	}

	void Node::SymetricalChecking(std::vector<int>& vec) {
        if (_left != nullptr && _right != nullptr)
        {
            vec.push_back(0);
            _left->SymetricalChecking(vec);
            _right->SymetricalChecking(vec);
        }
        else if (_left != nullptr)
        {
            vec.push_back(-1);
            _left->SymetricalChecking(vec);
        }
        else if (_right != nullptr)
        {
            vec.push_back(1);
            _right->SymetricalChecking(vec);
        }
        else
        {
            vec.push_back(2);
        }
	}

	void Node::Insert(Data NewData) {
		if (NewData.val < _data.val)
		{
			if (_left == nullptr){
                left_nodes++;
				_left = new Node(NewData);
                _left->_data.new_node = true;
			}
			else{
				_left->Insert(NewData);
			}

		}
		else if (NewData.val > _data.val)
		{
			if (_right == nullptr){
                right_nodes++;
				_right = new Node(NewData);
                _right->_data.new_node = true;
			}
			else{
				_right->Insert(NewData);
			}
		}
	}

    void Node::ResetLastLabel(){
        if (_left != nullptr){
            _left->_data.new_node = false;
            _left->ResetLastLabel();
        }

        if (_right != nullptr){
            _right->_data.new_node = false;
            _right->ResetLastLabel();
        }
    }

	bool Node::Contain(int number) {
		if (number < _data.val) {
			if (_left == nullptr){
				return false;
			}
			else {
				_left->Contain(number);
			}
		}
		else if (number > _data.val)
		{
			if (_right == nullptr) {
				return false;
			}
			else {
				_right->Contain(number);
			}
		}
		else {
			return true;
		}
	}

	int Node::GetSmallestNumber() {
		if (_left == nullptr){
			return _data.val;
		}
		else{
			_left->GetSmallestNumber();
		}
	}

	int Node::GetLargestNumber() {
		if (_right == nullptr) {
			return _data.val;
		}
		else {
			_right->GetLargestNumber();
		}
	}

	void Node::GetSortedVector(std::vector<int>& a)
	{
		if (_left != nullptr){
			_left->GetSortedVector(a);
		}
		a.push_back(_data.val);

		if (_right != nullptr){
			_right->GetSortedVector(a);
		}
	}

    std::vector<Data> Node::SetPositionOfNodesForVisualization(){
        int level{0},pos{1};
        this->SetLevel(level);
        this->SetPos(pos);
        this->SetDataForDrawing(*this);
        std::vector<Data> vec;
        this->ReturnDataVector(vec);

        return vec;

    }


    std::vector<QPoint> Node::GetVectorOfLinesBetwenNodes(){
        std::vector<QPoint> vec;
        this->LoopForLinesConnection(vec);
        return vec;
    }

    void Node::LoopForLinesConnection(std::vector<QPoint>& vec){

        if(_left != nullptr){
            QPoint point(_data.posX,_data.posY);
            vec.push_back(point);
            _left->LoopForLinesConnection(vec);
        }

        if(_right != nullptr){
            QPoint point(_data.posX,_data.posY);
            vec.push_back(point);
            _right->LoopForLinesConnection(vec);
        }

        QPoint point(_data.posX,_data.posY);
        vec.push_back(point);
    }

    void Node::ReturnDataVector(std::vector<Data>& vector){
        if(_left != nullptr){
            _left->ReturnDataVector(vector);
        }

        vector.push_back(_data);

        if(_right != nullptr){
            _right->ReturnDataVector(vector);
        }
    }


    void Node::SetDataForDrawing(Node& root){
        if(_left != nullptr){
            _left->SetDataForDrawing(root);
        }

        _data.posY = (_data.level* root.DrawingSize)+root.start_pos.y();
        if(_data.pos < root._data.pos){
            _data.posX = root.start_pos.x() - ((root._data.pos - _data.pos)*root.DrawingSize);
        }
        else if(_data.pos > root._data.pos){
            _data.posX = root.start_pos.x() + ((_data.pos - root._data.pos)*root.DrawingSize);
        }
        else{
            _data.posX = root.start_pos.x();
        }

        if(_right != nullptr){
            _right->SetDataForDrawing(root);
        }
    }

    void Node::SetPos(int &pos){
        if(_left != nullptr){
            _left->SetPos(pos);
        }
        _data.pos = pos;
        pos++;
        if(_right != nullptr){
            _right->SetPos(pos);
        }
    }

    void Node::SetLevel(int& level){
        _data.level = level;
        level++;
        if(_left != nullptr){
            _left->SetLevel(level);
        }
        if(_right != nullptr){
            _right->SetLevel(level);
        }
        level--;
    }
}
