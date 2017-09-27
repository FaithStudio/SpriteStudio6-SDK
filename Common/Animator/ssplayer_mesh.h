#pragma once
#ifndef __SSPLAYER_MESH__
#define __SSPLAYER_MESH__


class ISSTexture;

#define SSMESHPART_BONEMAX	(128)
#define SSMESHPART_CHECKRANGE (4)

struct StBoneWeight
{
	int		   		weight[SSMESHPART_BONEMAX];
	float		   	weight_f[SSMESHPART_BONEMAX];

	SsPartState*    bone[SSMESHPART_BONEMAX];
	SsVector3		offset[SSMESHPART_BONEMAX];

	int				bindBoneNum;

	float			length[SSMESHPART_BONEMAX];    //temp
	float			lengthtotal;  				   //temp

	int	getBoneNum() { return bindBoneNum; }

};

class SsMeshPart
{
public:


	float			*vertices;			//[3 * 10];///< ���W
	float			*colors;			//[4 * 10];	///< �J���[
	float			*weightColors;		//[4 * 10];	///< �E�F�C�g�F�����J���[
	float			*uvs;				//[2 * 10];		///< UV
	unsigned short	*indices;
	int				indices_num;
	int				tri_size;
	int				ver_size;
	float			*draw_vertices;		//[3 * 10];///< ���W

	std::vector<SsVector3>		calc_world_vertices;

	//�c�[���p�e���|�������[�N [editer]
	SsVector2*					vertices_outer;
	SsVector2*					update_vertices_outer;
	size_t						outter_vertexnum;

	std::vector<SsPartState*>   bindCandidateBoneList; //�o�C���h���[Editer]

public:
	StBoneWeight*   	bindBoneInfo;
	SsCell*  			targetCell;
	ISSTexture*			targetTexture;

	SsPartState*	   	myPartState;

	//�e���|���� [editor]
	bool				isBind;


public:
	SsMeshPart() :
		isBind(false), weightColors(0), bindBoneInfo(0), targetCell(0),
		vertices_outer(0), draw_vertices(0),
		vertices(0), colors(0), uvs(0), indices(0), update_vertices_outer(0), myPartState(0)
	{
	}


	SsMeshPart(SsPartState* s) :
		isBind(false), weightColors(0), bindBoneInfo(0), targetCell(0),
		vertices_outer(0), draw_vertices(0),
		vertices(0), colors(0), uvs(0), indices(0), update_vertices_outer(0)
	{
		myPartState = s;
	}

	~SsMeshPart()
	{
		Cleanup();
	}

	void	Cleanup();
	void	makeMesh();

	int		getVertexNum() { return ver_size; }
	StBoneWeight*	getVerticesWeightInfo(int index) {
		if (index > getVertexNum())return 0;
		return &bindBoneInfo[index];
	}

	void    updateTransformMesh();            //�Đ����p�@�i�o�C���h���ꂽ�{�[���ɉ����ĕό`���s���j

/*
	void	renderVertex();
	void	renderMesh(float alpha, bool renderTexture);
	void	renderBoneWeightColor(float alpha, bool renderTexture);
	void	update_matrix(float * matrix);  //�o�C���h�O�i�Z�b�g�A�b�v���[�h�p�̃}�g���N�X�A�b�v�f�[�g)

	void		calcVerticesPos(SsAnimeState* state);
	SsVector3   getWorldVertexPoint(int index) { return calc_world_vertices[index]; }
*/
//	Editer�p
//	void    verticesWeightColorCalc();
//	void	draw_world_vertices();
//	void	draw_world_vertices_once(int index, SsFColor c);
//	int 	isTouchVertex(float mx, float my);
//	bool  	isInPoint(float x, float y);
//	void    bindBoneSmoth(std::vector<SsPartState*>& list);

};



class SsPart;
class SsMeshPart;
//class SsAnimeState;

class   SsMeshAnimator
{
private:
	void	modelLoad();

public:
	SsAnimeDecoder* bindAnime;

	std::vector<SsPartState*>    	meshList;
	std::vector<SsPartState*>    	boneList;
	std::vector<SsPartState*>    	jointList;

public:
	SsMeshAnimator();
	virtual ~SsMeshAnimator() {}

	void	setAnimeDecoder(SsAnimeDecoder* s);

	void	update();
	void	makeMeshBoneList();


};




#endif
