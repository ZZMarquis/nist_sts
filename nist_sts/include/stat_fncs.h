#ifndef _STAT_FNCS_H_
#define _STAT_FNCS_H_

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     S T A T I S T I C A L  T E S T  F U N C T I O N  P R O T O T Y P E S 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "defs.h"

/**
 *
 * @param in
 * @param inl
 * @param out 外部预先分配缓冲区，缓冲区大小因最少为字节数的8倍
 * @param outbufsize
 * @return
 */
int BytesToBitSequence(unsigned char *in, int inl, BitSequence *outbuf, int bufsize);

/**
 * 单比特频数检测
 * @param n
 * @return
 */
int Frequency(int n, BitSequence *epsilon);

/**
 * 块内频数检测
 * @param M
 * @param n
 * @return
 */
int BlockFrequency(int M, int n, BitSequence *epsilon);

/**
 * 累加和检测
 * @param n
 * @return
 */
int CumulativeSums(int n, BitSequence *epsilon);

/**
 * 游程总数检测
 * @param n
 * @return
 */
int Runs(int n, BitSequence *epsilon);

/**
 * 块内最大“1”游程检测
 * @param n
 * @return
 */
int LongestRunOfOnes(int n, BitSequence *epsilon);

/**
 * 矩阵秩检测
 * @param n
 * @return
 */
int Rank(int n, BitSequence *epsilon);

/**
 * 离散傅立叶检测
 * @param n
 * @return
 */
int DiscreteFourierTransform(int n, BitSequence *epsilon);

/**
 * 非重叠模版匹配测试
 * @param m
 * @param n
 * @return
 */
int NonOverlappingTemplateMatchings(int m, int n, BitSequence *epsilon);

/**
 * 重叠模版匹配测试
 * @param m
 * @param n
 * @return
 */
int OverlappingTemplateMatchings(int m, int n, BitSequence *epsilon);

/**
 * 通用统计检测
 * @param n
 * @return
 */
int Universal(int n, BitSequence *epsilon);

/**
 * 近似熵检测
 * @param m
 * @param n
 * @return
 */
int ApproximateEntropy(int m, int n, BitSequence *epsilon);

/**
 * 自由游程测试
 * @param n
 * @return
 */
int RandomExcursions(int n, BitSequence *epsilon);

/**
 * 自由变量测试
 * @param n
 * @return
 */
int RandomExcursionsVariant(int n, BitSequence *epsilon);

/**
 * 线性复杂度检测
 * @param M
 * @param n
 * @return
 */
int LinearComplexity(int M, int n, BitSequence *epsilon);

/**
 * 重叠子序列检测
 * @param m
 * @param n
 * @return
 */
int Serial(int m, int n, BitSequence *epsilon);

/**
 * 二元推导检测
 * @param k
 * @param n
 * @param epsilon
 * @return
 */
int BinaryDerivate(int k, int n, BitSequence *epsilon, int epsilon_l);

/**
 * 自相关测试
 * @param d
 * @param n
 * @param epsilon
 * @return
 */
int SelfCorrelation(int d, int n, BitSequence *epsilon);

/**
 * 扑克检测
 * @param M
 * @param n
 * @param epsilon
 * @return
 */
int PokerDetect(int M, int n, BitSequence *epsilon);

/**
 * 游程分布检测
 * @param n
 * @param epsilon
 * @return
 */
int RunsDistribution(int n, BitSequence *epsilon);

#endif