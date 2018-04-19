
#include "astandSTDef.h"

int isSpecial(parseTree p);
int isSpecialNT(parseTree p);
int isSpecialT1(parseTree p);
int isSpecialT2(parseTree p);
int* numOfNTChil(parseTree p);
astNode newNode(parseTree p);
astNode newLeaf(parseTree p);
astNode newLeafMat(parseTree p);
astNode newLeafDualSp(parseTree p);
astNode newNodeDualSp(parseTree p);
astNode buildAstTree(parseTree p);
int isarithORbool(parseTree p);
astNode newNodeBool(parseTree p);
astNode newNodeArith(parseTree p);
void printAstTree(astNode ast);
int cal_sizeP(parseTree tree);
int cal_sizeA(astNode tree);