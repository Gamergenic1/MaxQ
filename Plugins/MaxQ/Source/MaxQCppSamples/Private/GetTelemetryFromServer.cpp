// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "GetTelemetryFromServer.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Spice.h"

// telemetry will use the celestrak server.
#define CELESTRAK_URL_BASE "https://celestrak.com"


//-----------------------------------------------------------------------------
// Name: IssueTelemetryRequest
// Desc:
// Fetch telemetry data from a SatCat (satellite catalog).
// It's tied to a specific server (celestrak) so it doesn't become an overly
// generalized "swiss army knife" used for more than intended.
// Exposed to Blueprints & the Blueprint samples also use this, because
// it's not implementable in Blueprints alone without a Third Party plugin.
//-----------------------------------------------------------------------------
UGetTelemetryFromServer_AsyncExecution* UGetTelemetryFromServer_AsyncExecution::IssueTelemetryRequest(UObject* WorldContextObject, FString ObjectId, FString Format)
{
    UGetTelemetryFromServer_AsyncExecution* Action = NewObject<UGetTelemetryFromServer_AsyncExecution>();
    Action->ObjectIdArg = ObjectId;
    Action->FormatArg = Format;
    Action->RegisterWithGameInstance(WorldContextObject);

    return Action;
}

//-----------------------------------------------------------------------------
// Name: UGetTelemetryFromServer_AsyncExecution Activate
// Desc:
// Implements async execution for IssueTelemetryRequest.
//-----------------------------------------------------------------------------
void UGetTelemetryFromServer_AsyncExecution::Activate()
{
    // Example URLs
    // https://celestrak.com/NORAD/elements/gp.php?CATNR=25544&FORMAT=TLE
    // https://celestrak.com/NORAD/elements/gp.php?GROUP=STATIONS&FORMAT=TLE
    // https://celestrak.com/NORAD/elements/gp.php?NAME=MICROSAT-R&FORMAT=JSON
    // https://celestrak.com/NORAD/elements/gp.php?INTDES=2020-025&FORMAT=JSON-PRETTY
    FString uriQuery = FString::Printf(TEXT(CELESTRAK_URL_BASE "/NORAD/elements/gp.php?%s&FORMAT%s"), *ObjectIdArg, *FormatArg);

    // Requires inclusion of Http module.
    // (MaxQCppSamples.Build.cs: PrivateDependencyModuleNames.Add("HTTP");)
    FHttpModule& httpModule = FHttpModule::Get();

    // Create an http request
    // The request will execute asynchronously, and call us back on the Lambda below
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> pRequest = httpModule.CreateRequest();

    FString RequestContent;

    // Set up the Http calls (GET vs POST et al, content type, URL).
    pRequest->SetVerb(TEXT("GET"));
    pRequest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));

    pRequest->SetURL(uriQuery);

    // Binds a "Lambda" callback.
    // The lambda does not execute immediately.  Rather, the function we're in
    // exits, and when the HTTP response is received the lambda will be called back.
    // (The lambda in turn will execute a callback delegate so the caller can handle the data.)
    pRequest->OnProcessRequestComplete().BindLambda(
        // This is a capture list.
        // It is necessary because the function executes & returns immediately, yet
        // the lambda needs access to some of the local variables that went out of scope.
        // The callback preserves the local variables so the Lambda has access to them.
        // In this specific case all we need is the pointer to the object (the 'this' pointer).
        [this](
            // Parameters the caller (http module) send into the callback.
            FHttpRequestPtr pRequest,
            FHttpResponsePtr pResponse,
            bool connectedSuccessfully) mutable {

                // Validate http called us back on the Game Thread...
                check(IsInGameThread());

                // Was the callback successful?
                if (connectedSuccessfully) {
                    // Yes!  Log it...
                    UE_LOG(LogTemp, Log, TEXT("Space-Track response: %s"), *(pResponse->GetContentAsString().Left(64)));

                    // ...and send the data to the user
                    this->OnSuccess.Broadcast(this->ObjectIdArg, pResponse->GetContentAsString());
                }
                else {
                    // No.  Mistakes were made.
                    FString Mistake;

                    switch (pRequest->GetStatus()) {
                    case EHttpRequestStatus::Failed:
                        if (pRequest->GetFailureReason() == EHttpFailureReason::ConnectionError)
                        {
                            Mistake = TEXT("Connection failed.");
                        }
                    default:
                        Mistake = TEXT("Request failed.");
                    }

                    UE_LOG(LogTemp, Error, TEXT("GetTelemetryFromServer Error: %s"), *Mistake);

                    // Confess the mistake but of course don't divulge any details to anyone.
                    this->OnError.Broadcast(this->ObjectIdArg, Mistake);
                }

                // Allow the UE Garbage Collector to free this object.
                this->SetReadyToDestroy();
        });

    UE_LOG(LogTemp, Log, TEXT("request: %s; content:%s"), TEXT(CELESTRAK_URL_BASE), *uriQuery);

    pRequest->ProcessRequest();
}


#undef CELESTRAK_URL_BASE