#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "PaperSprite.h"
#include "MySpriteFunctions.generated.h"


/**
 *
 */
UCLASS()
class COLDSTONES_API USpriteFunctions : public UBlueprintFunctionLibrary //Your project name in uppercase followed by "_API"
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Source Size", Keywords = "Source Texture Sprite"), Category = Custom) //Here you can change the keywords, name and category
		static FVector2D GetSourceSize(UPaperSprite* sprite);

};