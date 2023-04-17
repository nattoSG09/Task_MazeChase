#include "StageMap.h"

//�R���X�g���N�^
StageMap::StageMap(GameObject* parent)
	: GameObject(parent, "StageMap"),hModel_{},Width(0),Height(0),table_{}
{
	//CSV�f�[�^�̃��[�h
	{
		CsvMap_.Load("M_Map2.csv");

		Width = CsvMap_.GetWidth();
		Height = CsvMap_.GetHeight();

		//�z���Width�~Height�ŏ�����
		table_.resize(Width, vector<int>(Height, 0));

		for (int x = 0; x < Width; x++)
			for (int z = 0; z < Height; z++)
				table_[x][z] = CsvMap_.GetValue(x, ((Height - 1) - z));
	}
}

//������
void StageMap::Initialize()
{
	//object�̔z�u
	{
		for (int x = 0; x < Width; x++)
			for (int z = 0; z < Height; z++) {
				if (table_[x][z] == 0) {
					StageObject* FLOOR = Instantiate<StageObject>(GetParent());
					FLOOR->ObjectSet(OBJ_FLOOR);
					FLOOR->SetPosition(XMFLOAT3(x * 2, 0, z * 2));
				}
				else if (table_[x][z] == 1) {
					StageObject* WALL = Instantiate<StageObject>(GetParent());
					WALL->ObjectSet(OBJ_WALL);
					WALL->SetPosition(XMFLOAT3(x * 2, 0, z * 2));
				}
			}
	}
}

//�X�V
void StageMap::Update()
{
}

//�`��
void StageMap::Draw()
{
}

//�J��
void StageMap::Release()
{
	
}

bool StageMap::IsWall(int x, int z)
{
	return(table_[x/2][z/2] == OBJ_WALL);
}

//�v���[���n���̃A���S���Y���֐�
bool StageMap::HasWallBetween(XMFLOAT3 _posA, XMFLOAT3 _posB)
{
	//�v���C���[�̈ʒu�ƓG�̈ʒu�̊Ԃ̋��������߂�
	float distance = sqrt(pow(_posB.x - _posA.x, 2) + pow(_posB.z - _posA.z, 2));

	//2�_�Ԃ𓙕�����_�����
	float dx = (_posB.x - _posA.x) / distance;
	float dz = (_posB.z - _posA.z) / distance;
	float x = _posA.x;
	float z = _posA.z;

	//2�_�Ԃ���؂鐔�������[�v
	const int numPoints = (int)distance;

	// ���ʂ��`�F�b�N
	bool hasWall = false;

	for (int i = 0; i < numPoints; i++)
	{
		//�v���C���[�ƓG�̊Ԃɕǂ����邩�ǂ����𔻒�
		if (IsWall((int)(x), (int)(z)))
		{
			hasWall = true;
		}

		//���̓_�֐i��
		x += dx;
		z += dz;
	}

	//�ǂ��Ȃ��ꍇ��false��Ԃ�
	return hasWall;
}
