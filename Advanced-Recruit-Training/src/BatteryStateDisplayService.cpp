#include <QTextStream>

#include "BatteryData.h"
#include "BatteryStateDisplayService.h"
#include "I_BatteryDataSource.h"
#include "I_BatteryStateOfChargeService.h"

BatteryStateDisplayService::BatteryStateDisplayService(
    const I_BatteryDataSource& batteryDataSource,
    I_BatteryStateOfChargeService& batteryStateOfChargeService)
: batteryStateOfChargeService_(batteryStateOfChargeService)
{
    // This function is what "connects" the signal to the slot. So whenever the
    // signals it emitted, the slot will be called and the signal arguements
    // will be passed into the slot.
    connect(&batteryDataSource, SIGNAL(batteryDataReceived(const BatteryData&)),
        this, SLOT(handleBatteryDataReceived(const BatteryData&)));
}

BatteryStateDisplayService::~BatteryStateDisplayService()
{
}

void BatteryStateDisplayService::handleBatteryDataReceived(const BatteryData& batteryData)
{
    batteryStateOfChargeService_.addData(batteryData);
    QString Time = batteryStateOfChargeService_.timeWhenChargedOrDepleted().toString("hh:mm:ss:zzz");
    QString chargeDepletionDisplay;

    if (batteryData.current >= 0)
    {
        chargeDepletionDisplay = "time until fully depleted";
    }
    else
    {
        chargeDepletionDisplay = "time until fully charged";
    }

    QTextStream(stdout) << "Voltage: " << batteryData.voltage
        << " Current: " << batteryData.current
        << " Total Ah used: " << batteryStateOfChargeService_.totalAmpHoursUsed() << endl;
}
