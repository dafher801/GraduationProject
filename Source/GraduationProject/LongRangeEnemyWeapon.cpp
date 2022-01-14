
#include "LongRangeEnemyWeapon.h"

ALongRangeEnemyWeapon::ALongRangeEnemyWeapon()
{

}

void ALongRangeEnemyWeapon::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);
}
