#ifndef SCANS_H_INCLUDED
#define SCANS_H_INCLUDED
#include <memory>
#include "objects.h"
class Trait;
struct ScanInfo // a class that represents all the information one can get from scanning something
{
    std::shared_ptr<Trait> trait;
};
struct ScanComponent : public Component
{
    bool done = false;
    int scanTime = 0; //amount of time for the creature to be scanned
    int maxScanTime = 0;//amount of time for the creature to be scanned
    ScanInfo info;
    bool scanning = false;
    void update(SpriteComponent* sprite);
    void setScanning(bool value); //if value is true, start the scanning
    void setScanTime(int time);


};
extern ScanComponent SharkScan;
void initScans();

#endif // SCANS_H_INCLUDED
