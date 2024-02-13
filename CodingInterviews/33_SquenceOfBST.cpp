#include <cstdio>

// BST：Binary Search Tree，二叉搜索树
bool VerifySquenceOfBST(int sequence[], int length)
{
	if (sequence == nullptr || length <= 0)
		return false;

	int root = sequence[length - 1];

	// 在二叉搜索树中左子树的结点小于根结点
	int i = 0;
	for (; i < length - 1; ++i)
	{
		if (sequence[i] > root)
			break;
	}

	// 在二叉搜索树中右子树的结点大于根结点
	int j = i;
	for (; j < length - 1; ++j)
	{
		if (sequence[j] < root)
			return false;
	}

	printf("i=%d---j=%d---root=%d\n", i, j, root);
	// 判断左子树是不是二叉搜索树
	bool left = true;
	if (i > 0)
		left = VerifySquenceOfBST(sequence, i);

	// 判断右子树是不是二叉搜索树
	bool right = true;
	if (i < length - 1)
		right = VerifySquenceOfBST(sequence + i, length - i - 1);

	return (left && right);
}