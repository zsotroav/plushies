# Plush Monsters' fight club <br /> PROGRAM PLAN

> **Disclaimer:**
The following diagrams only show the most important parts of the application
and may not contain every implemented function or the exact way they were 
implemented. This is only a high-level overview and not an exact description.

## Attacks
When attacking, both players choose their attack and send it to the Server
which distributes the attacks

```mermaid
classDiagram
    direction LR
    ActionContext "2" --> "1" Server : contains

    class ActionContext {
        +int attackPower
        +int attackSpeed
        +type actionType
        +Plush& foe
    }

    class Server {
        -ActionContext actions[2]
        -Player Players[2]
        +void addAction(ActionContext a)
    }
```

## Plush classes
```mermaid
classDiagram
    direction LR
    type "1..2" --> "1" Brand : has
    type "1" --> "1" Action : has
    Action "1..4" --> "1" Plush : knows
    Plush "1..*" --* "1" Brand : brand id

    class Brand {
        -int id
        -type baseType
        -type secondaryType
        -int baseStats[6]
    }

    class Plush {
        -int brand
        -int UV[6]
        -int HP
        +Action Actions[4] 
        +int operator>>(int atSlot)
        +void operator<<(int hp)
        +int getHP()
        +int getBrand()
    }

    class type{
        <<enum>>
        Normal
        Grass
        Water
        Fire
        ...
        +int operator>>(type target)
    }

    class Action {
        -int Damage
        -int Accuracy
        -double Priority
        -type Type
        +int getDamage()
        +int getType()
        +double getAbsSpeed(int base)
        +double getSpeed()
    }
```

## Player classes
The overlord (AI player) classes inherit the player class and overrides the
ready function with their attack logic. 

```mermaid
classDiagram
    direction TD

    Player <|-- Overlord : Inherits

    class Player {
        -Plush plushes[]
        -int plushCount

        +void addPlush(Plush* p)
        +int numPlush(bool alive = false)
        +virtual ready(Plush& foe) Server asks for attack
    }

    class Overlord {
        +void ready(Plush& foe)
    }
```

## Flowchart
goes brrr

```mermaid
flowchart TD
    srv[Server] -- "Ready for attack" --> Player --> ask

    ask(move selection)

    ask -- "choice" --> srv

    srv -- "Got da 2 choices" --> logic(Attack logic and order) 
    -. "Results" .-> Player

```