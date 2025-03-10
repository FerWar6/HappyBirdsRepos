# TDD AgeOfWar Game 

## Mechanics
- DataManager Class
    - int Money
    - int Experience


- Units Class
    - bool isEnemy
    - int unitHealth
    - float movementSpeed
    - int meleeDamage
    - float meleeAttackSpeed
    - int rangedDamage
    - float rangedAttackSpeed
    - float sightRange
    - bool opponentInRange
    - float spawnTime

    - int expValue
    - int moneyValue

    - opponentInRange is true if the distance to the nearest opponent is smaller than sightRange
    - (the enemy and player bases are both also enemy's, so the unit will attack if in range)

    - move if opponentInRange is false
    - if isEnemy is false, move the unit from left to right
    - if isEnemy is true, move the unit from right to left

    - if opponentInRange is true, call the function Attack()
    - Attack() hits the enemy in front of it IF it doesnt have a rangedDamage and rangedAttackSpeed

    - MoveUnit() is a simple function that moves the unit towards the opponents base

- Turret Class
    - bool isEnemy
    - int turretDamage
    - float shootingSpeed
    - float sightRange
    - bool opponentInRange

    - int moneyCost

    - opponentInRange is true if the distance to the nearest opponent is smaller than sightRange

    - the turret will shoot a projectile if the opponent is in sight range

- Shop Class
    - the player can buy different Units in the shop, if you have enough money you can buy these units and they will spawn in front of your base
    - Units take time to train, you can queue up upto five units at a time

    - the player can buy different Turrets in the shop, if you have enough money you can place the turret on any available space on your base
    - the player can sell Turrets, if you choose to sell a turret you will regain half its cost
    - the player can buy additional Turret slots, adding an available slot for a Turret onto your base

    - once the player has the required amount of experience, they can click a button to evolve to the next age

- Base Class
    - bool isEnemy
    - int health

    - if the health of the players base reaches 0, the player loses
    - if the health of the enemys base reaches 0, the player wins

- Start Menu
    - Start button opens a dificulty tab where the player can choose from the following dificulties
        - easy
        - hard
        - impossible

    - Quit button
    - the quit button closes the game
