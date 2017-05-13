#include "SFApp.h"
SFApp::SFApp(std::shared_ptr<SFWindow> window) : fire(0), is_running(true), sf_window(window), score(0) 



{
  int canvas_w, canvas_h;
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);

int i = 0;



  app_box = make_shared<SFBoundingBox>(Vector2(canvas_w, canvas_h), canvas_w, canvas_h);
  bottomwall = make_shared<SFAsset>(SFASSET_BOTTOMWALL, sf_window);
  auto bottomwall_pos = Point2(canvas_w/2, 16);
  bottomwall->SetPosition(bottomwall_pos);

  app_box = make_shared<SFBoundingBox>(Vector2(canvas_w, canvas_h), canvas_w, canvas_h);
  leftwall = make_shared<SFAsset>(SFASSET_LEFTWALL, sf_window);
  auto leftwall_pos = Point2(16, canvas_h/2);
  leftwall->SetPosition(leftwall_pos);

  app_box = make_shared<SFBoundingBox>(Vector2(canvas_w, canvas_h), canvas_w, canvas_h);
  topwall = make_shared<SFAsset>(SFASSET_TOPWALL, sf_window);
  auto topwall_pos = Point2(canvas_w/2, 704);
  topwall->SetPosition(topwall_pos);

  app_box = make_shared<SFBoundingBox>(Vector2(canvas_w, canvas_h), canvas_w, canvas_h);
  rightwall = make_shared<SFAsset>(SFASSET_RIGHTWALL, sf_window);
  auto rightwall_pos = Point2(1264, canvas_h/2);
  rightwall->SetPosition(rightwall_pos);

   app_box = make_shared<SFBoundingBox>(Vector2(canvas_w, canvas_h), canvas_w, canvas_h);
  gameover = make_shared<SFAsset>(SFASSET_GAMEOVER, sf_window);
  auto gameover_pos = Point2(640, 360);
  gameover->SetPosition(gameover_pos);


  app_box = make_shared<SFBoundingBox>(Vector2(canvas_w, canvas_h), canvas_w, canvas_h);
  background = make_shared<SFAsset>(SFASSET_BACKGROUND, sf_window);
  auto background_pos = Point2(640, 360);
  background->SetPosition(background_pos);

 
 


  app_box = make_shared<SFBoundingBox>(Vector2(canvas_w, canvas_h), canvas_w, canvas_h);
  player  = make_shared<SFAsset>(SFASSET_PLAYER, sf_window);
  auto player_pos = Point2(canvas_w/2, 70);
  player->SetPosition(player_pos);

  
 


  


  





  const int number_of_aliens = 10;
  for(int i=0; i<number_of_aliens; i++) {
    // place an alien at width/number_of_aliens * i
    auto alien = make_shared<SFAsset>(SFASSET_ALIEN, sf_window);
    auto pos   = Point2(((canvas_w/number_of_aliens) * i) + 60, 300.0f);
    alien->SetPosition(pos);
    aliens.push_back(alien);
  
}

//generates another unique array of aliens that are placed above the first
  const int number_of_aliens1 = 12;
for(int i=1; i<number_of_aliens1; i++) {
    // place an alien at width/number_of_aliens * i
    auto alien = make_shared<SFAsset>(SFASSET_ALIEN, sf_window);
    auto pos   = Point2(((canvas_w/number_of_aliens1) * i) + 60, 400.0f);
    alien->SetPosition(pos);
    aliens.push_back(alien);
  
}

//determines the co-ordinates and properties of the game's "mothership" - which is represented in-game as a giant "alien" sprite
 const int number_of_motherships = 1;
  for(int i=0; i<number_of_aliens; i++) {
    // place an alien at width/number_of_aliens * i
    auto mothership = make_shared<SFAsset>(SFASSET_MOTHERSHIP, sf_window);
    auto pos   = Point2(((canvas_w/number_of_motherships) * i) + 60, 600.0f);
    mothership->SetPosition(pos);
    motherships.push_back(mothership);
  
}

//generates an array of "asteroids"
const int number_of_asteroids = 11;
    for(int i=0; i<number_of_asteroids; i++) {
    auto asteroid = make_shared<SFAsset>(SFASSET_ASTEROID, sf_window);
    auto pos = Point2(((canvas_w/number_of_asteroids) * i) + 60, 500.0f);
    asteroid->SetPosition(pos);
    asteroids.push_back(asteroid);

}

//generates the game's golden coin
  auto coin = make_shared<SFAsset>(SFASSET_COIN, sf_window);
  auto pos  = Point2((canvas_w/2), 700);
  coin->SetPosition(pos);
  coins.push_back(coin);

} 

  
  


SFApp::~SFApp() {
}

/**
 * Handle all events that come from SDL.
 * These are timer or keyboard events.
 */
void SFApp::OnEvent(SFEvent& event) {
  SFEVENT the_event = event.GetCode();
  switch (the_event) {
  case SFEVENT_QUIT:
    is_running = false;
    break;
  case SFEVENT_UPDATE:
    OnUpdateWorld();
    OnRender();
    break;
  case SFEVENT_PLAYER_LEFT:
    player->GoWest();
    break;
  case SFEVENT_PLAYER_RIGHT:
    player->GoEast();
    break;

//if the player presses the "Up" arrow key, the player sprite will go up
  case SFEVENT_PLAYER_UP:
    player->GoNorth();
    break;

//if the player presses the "Down" arrow key, the player sprite will go down
  case SFEVENT_PLAYER_DOWN:
    player->GoSouth();
    break;
  case SFEVENT_FIRE:
    fire ++;
    FireProjectile();
    break;
  }
}

int SFApp::OnExecute() {
  // Execute the app
  SDL_Event event;
  while (SDL_WaitEvent(&event) && is_running) {
    // wrap an SDL_Event with our SFEvent
    SFEvent sfevent((const SDL_Event) event);
    // handle our SFEvent
    OnEvent(sfevent);
  }
}

int SFApp::Counter() {
	i++;
	if(i == 320) {
	i = 0;
}
}

void SFApp::OnUpdateWorld() {
  // Update projectile positions
  for(auto p: projectiles) {
    p->PlayerBulletNorth(); //a new class has been made in order to make the movement speed of the projectile separate from the movement speed of the player
  }



  // Update enemy positions
  //determines the basic artifical intelligence of the mothership
  for(auto mothership : motherships) {
Counter();
if( i >= 0 && i < 160) {
mothership->GoEast2();
break;
}


if ( i>= 160 & i < 320) {
mothership->GoWest2();
break;
}
}
  

  // Detect collisions
  for(auto projectile : projectiles) {
    for(auto alien : aliens) {
      
      if(projectile->CollidesWith(alien)) {
    
        projectile->SetNotAlive(); //if the projectile hits an enemy, then the projectile will disappear from the game completely, preventing it from hitting other enemies 
        alien->HandleCollision();
     score += 50; //the player's score will by increase by fifty points
      std::cout << "Take that, alien scum!" << std::endl; //these comments will appear in the Linux command line
      std::cout << "Score: " << score << std::endl;
     }
      }
    }
  








for(auto projectile : projectiles) {
    for(auto asteroid : asteroids) {
      if(projectile->CollidesWith(asteroid)) {
        projectile->SetNotAlive();
        asteroid->HandleCollision();
        score += 100;
      std::cout << "No mere asteroid shall stand in the way of your journey!" << std::endl;
      std::cout << "Score: " << score << std::endl;
      }
    }
  }

for(auto projectile : projectiles) {
    for(auto mothership : motherships) {
      if(projectile->CollidesWith(mothership)) {
        projectile->SetNotAlive();
        mothership->HandleCollision();
        score += 100;
      std::cout << "The mothership is destroyed! Now go and recieve your treasure!" << std::endl;
      std::cout << "Score: " << score << std::endl;
      }
    }
  }


//if the player collides with an asteroid, an alien or the mothership, then the player will automatically lose the game
//if the player collides with a coin, then the player will automatically win the game
    for(auto coin : coins) {
      if(player->CollidesWith(coin)) {
        coin->HandleCollision();
        score += 500;
        std::cout << "Wow! You've collected  a golden coin! You win!" << std::endl;
      std::cout << "Score: " << score << std::endl;
      }
    }

for(auto asteroid : asteroids) {
      if(player->CollidesWith(asteroid)) {
        player->HandleCollision();
        asteroid->HandleCollision();
      std::cout << "Oh no! Your spaceship has been hit by a giant meteor!" << std::endl;
      }
    }


    for(auto alien : aliens) {
      if(player->CollidesWith(alien)) {
        player->HandleCollision();
        alien->HandleCollision();
     std::cout << "The aliens have taken you and your crew hostage! So much for a happy ending!" << std::endl;
      }
    }


for(auto mothership : motherships) {
      if(player->CollidesWith(mothership)) {
        player->HandleCollision();
        mothership->HandleCollision();
     std::cout << "You have been taken hostage by the mothership! What horrid fate awaits you now?!" << std::endl;
      }
    }




//if the player collides with any of the four walls, then the sprite will automatically "bounce" back to prevent it from going out of bounds
   if(player->CollidesWith(bottomwall)) {
      player->HandleCollision();
      std::cout << "Your spaceship has been vapourised by a giant laser!" << std::endl;
    }

if(player->CollidesWith(leftwall)) {
 player->EastWallCollision();
std::cout << "What is this strange gravitational force? Whatever it is, it's not letting you escape!" << std::endl;
}

if(player->CollidesWith(rightwall)) {
 player->GoWest();
std::cout << "What is this strange gravitational force? Whatever it is, it's not letting you escape!" << std::endl;
}

if(player->CollidesWith(topwall)) {
 player->GoSouth();
std::cout << "What is this strange gravitational force? Whatever it is, it's not letting you escape!" << std::endl;
}

for(auto alien : aliens) {




}


   


  // remove dead aliens (the long way)
  list<shared_ptr<SFAsset>> tmp_aliens;
 for(auto alien : aliens) {
    if(alien->IsAlive()) {
      tmp_aliens.push_back(alien);
    }
  }
  aliens.clear();
  aliens = list<shared_ptr<SFAsset>>(tmp_aliens);


 
// removes the dead mothership
list<shared_ptr<SFAsset>> tmp_motherships;
 for(auto mothership : motherships) {
    if(mothership->IsAlive()) {
      tmp_motherships.push_back(mothership);
    }
  }
  motherships.clear();
  motherships = list<shared_ptr<SFAsset>>(tmp_motherships);



  



//removes the coin if it has been collected by the player
list<shared_ptr<SFAsset>> tmp_coins;
 for(auto coin : coins) {
    if(coin->IsAlive()) {
      tmp_coins.push_back(coin);
    }
  }
  coins.clear();
  coins = list<shared_ptr<SFAsset>>(tmp_coins);


//removes the player[s projectiles
list<shared_ptr<SFAsset>> tmp_projectiles;
 for(auto projectile : projectiles) {
    if(projectile->IsAlive()) {
      tmp_projectiles.push_back(projectile);
    }
  }
  projectiles.clear();
  projectiles = list<shared_ptr<SFAsset>>(tmp_projectiles);


//removes the asteroids
list<shared_ptr<SFAsset>> tmp_asteroids;
 for(auto asteroid : asteroids) {
    if(asteroid->IsAlive()) {
      tmp_asteroids.push_back(asteroid);
    }
  }
  asteroids.clear();
  asteroids = list<shared_ptr<SFAsset>>(tmp_asteroids);




}




void SFApp::OnRender() {
  SDL_RenderClear(sf_window->getRenderer());

  // draw the player



topwall->OnRender();
  leftwall->OnRender();
  rightwall->OnRender();




  
background->OnRender(); //the game renders the background so that it is "above" the top, left and right walls and "below" the bottom wall




  bottomwall->OnRender(); //unlike the other three walls, the bottom wall is an obstacle that will cause harm to the player if a collision takes place
  
  



  for(auto projectile: projectiles) {
    if(projectile->IsAlive()) 
    {projectile->OnRender();}
  }

  for(auto alien: aliens) {
    if(alien->IsAlive()) {alien->OnRender();}
  }

  for(auto coin: coins) {
    if(coin->IsAlive()) {coin->OnRender();}
  }
  
  for(auto asteroid: asteroids) {
    if(asteroid->IsAlive()) {asteroid->OnRender();}
}

for(auto mothership: motherships) {
    if(mothership->IsAlive()) {mothership->OnRender();}
}

if(player->IsAlive()) 
   {player->OnRender();}
    else{gameover->OnRender();}
//if the player is dead, then the "Game Over" screen will appear


  // Switch the off-screen buffer to be on-screen
  SDL_RenderPresent(sf_window->getRenderer());
}

void SFApp::FireProjectile() {
  auto pb = make_shared<SFAsset>(SFASSET_PROJECTILE, sf_window);
  auto v  = player->GetPosition();
 
  pb->SetPosition(v);

  projectiles.push_back(pb);
}

