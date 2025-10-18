// I used a lot of copyrightable things here


#include "Origins_Table.h"

UOrigins_Table::UOrigins_Table()
{
    // Example Origin #1
    FOrigins Origin1;
    Origin1.Name = FText::FromString(TEXT("Children of the Stars"));
    Origin1.Ability1 = FText::FromString(TEXT("Starlight Vision"));
    Origin1.Ability2 = FText::FromString(TEXT("Celestial Memory"));
    Origin1.Description = FText::FromString(TEXT("A mystic people said to descend from fallen stars."));
    Origin1.Origin_ID = 1.0f;
    Origin1.bSecondNegative = false;
    Origin1.Start_Date = EOriginStart::Ancient;   // <-- your enum

    OriginsList.Add(Origin1);

    // Example Origin #2
    FOrigins Origin2;
    Origin2.Name = FText::FromString(TEXT("The Steamforged"));
    Origin2.Ability1 = FText::FromString(TEXT("Mechanical Ingenuity"));
    Origin2.Ability2 = FText::FromString(TEXT("Iron Will"));
    Origin2.Description = FText::FromString(TEXT("Forged in the age of engines, they thrive on invention."));
    Origin2.Origin_ID = 2.5f;
    Origin2.bSecondNegative = true;
    Origin2.Start_Date = EOriginStart::Modern;

    OriginsList.Add(Origin2);

    // Example Origin #3
    FOrigins Origin3;
    Origin3.Name = FText::FromString(TEXT("The Dreamweavers"));
    Origin3.Ability1 = FText::FromString(TEXT("Illusion Craft"));
    Origin3.Ability2 = FText::FromString(TEXT("Shared Dreams"));
    Origin3.Description = FText::FromString(TEXT("Masters of imagination, they shape reality through visions."));
    Origin3.Origin_ID = 3.7f;
    Origin3.bSecondNegative = false;
    Origin3.Start_Date = EOriginStart::Future;

    OriginsList.Add(Origin3);
}



