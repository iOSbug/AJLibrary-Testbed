//
//  AJMessage.h
//  AJLibrary
//
//  Created by Tianbao Wang on 2022/9/22.
//

#import <Foundation/Foundation.h>
#import <UserNotifications/UserNotifications.h>
#import "AJError.h"
#import "AJAlertSurveyModel.h"
#import "AJAlertsCalendarModel.h"
#import "AJAlertsListModel.h"

NS_ASSUME_NONNULL_BEGIN

typedef enum : NSUInteger {
    PushSettingTypeUpsert,
    PushSettingTypeRemove
} PushSettingType;

@interface AJMessage : NSObject

/**
*    单例
*/
+ (instancetype)shared;

/**
 *    初始化推送参数
 */
- (void)initPush;

/**
 *    初始化推送参数，回调获取到的firebase的deivcetoken
 */
- (void)initPush:(nullable void (^)(NSString *))deviceToken;

/**
 *    设置firebase的pushtoken
 */
- (void)setFirebasePushToken:(NSString *)deviceToken;

/**
 *    处理推送消息
 *    @param     notiResponse               推送消息
 */
- (void)handleApnsNotiReponse:(UNNotificationResponse *)notiResponse;

/**
 *    获取设备告警消息概览
 *
 *    @param     success                成功 回调
 *    @param     failure                失败回调
 */
- (void)queryAlertsSurvey:(nullable void (^)(NSArray<AJAlertSurveyModel *> *))success
                  failure:(nullable void (^)(AJError *))failure;


/// 获取含有告警视频的日历小蓝点
/// @param deviceId 设备 ID
/// @param tzValue  设备时区，从 camera.timeConfig.tzValue 获取
/// @param accessKey 密钥，从 camera.base.accessKey 获取
/// @param success success
/// @param failure failure
- (void)fetchAlertsCalendar:(NSString *)deviceId
                    tzValue:(NSString *)tzValue
                  accessKey:(NSString *)accessKey
                    success:(nullable void (^)(AJAlertsCalendarModel *))success
                    failure:(nullable void (^)(AJError *))failure;



/// 获取告警列表
/// @param deviceId 设备ID
/// @param accessKey 密钥，从 camera.base.accessKey 获取
/// @param tzValue 设备时区，从 camera.timeConfig.tzValue 获取
/// @param today 是否为今日, 若是:1, 否则:0
/// @param todayFirst 今天的第一次拉取，是为1，否为0
/// @param ctime 20180711000000, // 数值
/// @param cdate 摄像头时区的日期，20180710
/// @param limit 每页数量, 缺省值: 10
/// @param success success
/// @param failure failure
- (void)getAlertsList:(NSString *)deviceId
            accessKey:(NSString *)accessKey
              tzValue:(NSString *)tzValue
                today:(NSString *)today
           todayFirst:(NSString *)todayFirst
                ctime:(NSString *)ctime
                cdate:(NSString *)cdate
                limit:(NSString *)limit
              success:(nullable void (^)(AJAlertsListModel *))success
              failure:(nullable void (^)(AJError *))failure;


/**
 *    加载摄像头告警页面
 *    @param     deviceId              摄像头id
 *    @param     date                       展示告警的日期 (格式：yyyyMMdd，若传空，则展示最新一天的数据)
 */
- (void)startAlertView:(NSString *)deviceId
                  date:(NSString *)date;


/// 推送配置
/// @param deviceId 设备ID
/// @param aliasName 推送通知设备名称
/// @param devEmcUrl 设备接入 devEmcUrl 地址
/// @param settingType 推送配置方式 PushSettingTypeUpsert - 更新，PushSettingTypeRemove - 移除
/// @param clearPushToken 分享设备的退出登录操作和关闭推送开关操作，传 OrderTypeUpsert 并且 clearPushToken  为 YES
/// @param success success
/// @param failure failure
- (void)pushSetting:(NSString *)deviceId
          aliasName:(NSString *)aliasName
          devEmcUrl:(NSString *)devEmcUrl
          orderType:(PushSettingType)settingType
     clearPushToken:(BOOL)clearPushToken
            success:(nullable void (^)(void))success
            failure:(nullable void (^)(AJError *))failure;


@end

NS_ASSUME_NONNULL_END
