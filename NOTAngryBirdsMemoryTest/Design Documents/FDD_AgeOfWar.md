# FDD AquaMystics Game 

## General description
a "recreation" of Age Of War, an old flash game with OpenGL from nothing

### Dynamics
Resource Management: gain money, choose where to spend your money or to save it.

Strategic Defense: Defend your castle from enemies.

Risk and Reward: Deciding whether to save currency for bigger upgrades or spend on defending your base.

## Functional requirements
Turrets:
- Players can buy turrets to be permanently defend their base.
- Turrets will shoot enemies when they get close to your base.
- Players will start with one turret slot, but can buy additional turret slots for more money.
- The selection of turrets players can buy changes each age.
- The player has the ability to sell a turret for half the cost of the turret.
- The different kinds of turrets may include: 
    - A fast shooting turret with low damage
    - A slow shooting turret with high damage
    - A turret with extreamly high damage, but short range.
    - A turret that shoots an object that explodes on impact, damaging other nearby enemies.

Guardian:
- Players can buy guardians to defend their base.
- Guardians will spawn right in front of your base and move towards the Enemy base.
- If a defending entity comes across an enemy it will stop moving and attack the enemy.
- The selection of defending entities players can buy will change each age.
- The different kinds of Guardians may include:
    - A guardian that attacks at short a range.
    - A guardian that can attack from a distance, but has lower health.
    - A guardian that has a lot of health, but does very little damage.
- The Guardians a player can choose from is identical to the guardians the enemy can choose.

Currency:
- Players get currency from killing enemies.
- Players can spend this currency on various items in the shop, (Guardians, Turrets).

Experience:
- Players can earn experience from killing enemies.
- when the player has earned enough experience, they are able to upgrade to a new age.

Enemies:
- Enemies will spawn right in front if the enemy base and move towards the players base.
- If an enemies comes across a guardian it will stop moving and attack the guardian.

Ages:
- There are 5 ages in the game.
- If the player has earned enough experience he can evolve to the next game.
- each age has unique Guardians/enemies, abilities and Turrets.

Gameplay Loop:
- The player can win by destroying the enemy base.
- The player loses if their own base is destroyed by enemies.

### Performance
* The game should not lag or reduce below 60 frames per second, even while the player and enemies are shooting.

#### MoSCoW Tabel
- Must Haves:
    - Guardians.
    - Enemies.
    - Currency.
    - Experience.
    - Ages.
    - Gameplay Loop.
    - Shop to spend money.
- Should Haves:
    - Turrets.
    - Good looking visuals.

- Could Haves:
    - Animations
    - Different difficulties.
    - Smart Enemy AI (the computer you play against).
- Won't Haves: