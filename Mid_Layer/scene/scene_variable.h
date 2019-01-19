#ifndef SCENE_VARIABLE_H
#define SCENE_VARIABLE_H

#include "platform_common.h"


#define SCENE_RTT_DEBUG	3
#if (1 == SCENE_RTT_DEBUG)	// ����ȼ�
#define SCENE_RTT_LOG(...)
#define SCENE_RTT_WARN(...)
#define SCENE_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_RTT_DEBUG)	// ����ȼ�
#define SCENE_RTT_LOG(...)
#define SCENE_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_RTT_DEBUG)	// ���Եȼ�
#define SCENE_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define SCENE_RTT_LOG(...)
#define SCENE_RTT_WARN(...)
#define SCENE_RTT_ERR(...)
#endif

#define SCENE_STORE_TIMEOUT	(28800)	// �������ݴ洢��ʱʱ�䣬8Сʱ
#define SCENE_WARN_CHECK_INTERVAL	(60)	// �������������������ʳ���

/* ����������ʽ */
typedef enum
{
	eSceneMeasureIM,	// instant messaging ��ʱ����
	eSceneMeasureBG,	// background  ��̨����
	eSceneMeasureKeep,	// ���֣���������
}eSceneMeasureWay;

#endif



