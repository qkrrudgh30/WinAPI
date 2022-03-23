// GameEngineLevel.h

#pragma once
#include "GameEngineBase/GameEngineNameObject.h"
#include <list>
#include <map>

// 설명 :
class GameEngine;
class GameEngineActor;
class GameEngineLevel : public GameEngineNameObject
{
    friend GameEngine;
public:
    // constrcuter destructer
    GameEngineLevel();
    virtual ~GameEngineLevel();

    // delete Function
    GameEngineLevel(const GameEngineLevel& _Other) = delete;
    GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
    GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
    GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:
    virtual void Loading() = 0;
    virtual void Update() = 0;
    virtual void LevelChangeStart() {}
    virtual void LevelChangeEnd() {}

    template<typename ActorType>
    ActorType* CreateActor(const std::string& _Name, int _Order)
    {
        ActorType* NewActor = new ActorType();
        GameEngineActor* StartActor = NewActor;
        NewActor->SetName(_Name);
        NewActor->SetLevel(this);
        StartActor->Start();

/*
    map에서 [] 연산자는 find와 insert를 동시에 함.
    즉, 아래와 같이 동작하는 것.
    std::map<int, std::list<GameEngineActor*>>::iterator FindGroup = AllActor_.find(_Order);

    if (FindGroup == AllActor_.end())
    {
        AllActor_.insert(std::map<int, std::list<GameEngineActor*>>::value_type(_Order, std::list<GameEngineActor*>()));
        // == AllActor_.insert(std::make_pair(_Order, std::list<GameEngineActor*>())); 같은 코드지만, 위 코드가 좀 더 빠름.
    }
*/
        std::list<GameEngineActor*>& Group = AllActor_[_Order];
        Group.push_back(NewActor);

        //// _Order 액터들이 돌아가는 순서를 의미하게 된다.
        //// insert와 find를 동시에 하게 됩니다.
        //
        //	

        //
        //{

        //	// 
        //	// 이게더 빠릅니다.
        //	
        //	FindGroup = AllActor_.find(_Order);
        //}

        return nullptr;
    }

private:
    std::map<int, std::list<GameEngineActor*>> AllActor_;

    void ActorUpdate();
    void ActorRender();

};

