#include "scans.h"
#include "game.h"
ScanComponent SharkScan;
void initScans()
{
    SharkScan.setScanTime(1000);
    SharkScan.info.trait.reset(new speedUp);
}
void ScanComponent::setScanning(bool value) //if value is true, start the scanning
{
    scanning = value;
}
void ScanComponent::update(SpriteComponent* sprite)
{
    if (!done)
    {
        if (scanning && scanTime > 0 )
        {
            sprite->request = &RenderController::scanning;
            sprite->request->setVec3fv("shade",{abs(sin(SDL_GetTicks()/100.0)),abs(sin(SDL_GetTicks()/1000.0)),abs(sin(SDL_GetTicks()))});
            scanning = false;
            scanTime -= Game::deltaTime;
        }
        else if (!scanning)
        {
            scanTime = std::min(scanTime + Game::deltaTime*1.5, (double)maxScanTime);
        }
        else if (scanTime <= 0)
        {
            done = true;
            Game::traitList.push_back(info.trait.get());
        }
    }
}
void ScanComponent::setScanTime(int time)
{
    maxScanTime = time;
    scanTime = maxScanTime;
}
