var Scene3dController = function(idDiv, _shotFn, _loadEndCallBack){
	//private members / methods
	var self = this,
		container = document.getElementById(idDiv),
		$container = $('#'+idDiv),
		$gameLoader = $('#gameLoader'),
		width = window.innerWidth,
	    height = window.innerHeight,
	    shotFunction = _shotFn,
	    loadEndCallback = _loadEndCallBack || false,
	    STARTED = false,
	    MOVABLE = false,
	    garbageCollector = [];
		objects = {
			balls : [],
			targets : [],
			myBall : null,
			light : null,
	    	world : null,
	    	line : null,
		},
		threeMainObj = {
			scene : null,
		    renderer : null,
		    controls : null,
		    stats: null
		},
	    cameras = {
	    	leftcamera : null,
	    	rightcamera : null
	    },
	    dnd = {
	    	SELECTED : null,
			INTERSECTED : null,
			mouse : new THREE.Vector2(),
			offset : new THREE.Vector3(),
			dndPlane : null,
			projector : null,
		},
		options = {
			shadows : true,
			ballRadius : 100,
			ballQ: 24,
			targetRadius : 200,
			targetQ: 40,
			dualView: false,
			stats: true
		},
		init = function(){
			initMainComponents();
			initLight();
			initWorld();
			initDnDPlane();

			objects.myBall = Creator3D.createBall(game.player.getColor(), options.ballRadius, options.ballQ);
			threeMainObj.scene.add(objects.myBall);

			self.setShadows(options.shadows);
			if(options.stats) initStats();

			window.addEventListener( 'resize', onWindowResize, false );
			garbageCollector.push(objects.myBall);
			garbageCollector.push(dnd.mouse);
			garbageCollector.push(dnd.offset);
		},
		initMainComponents = function(){
			cameras.leftcamera = new Creator3D.createCamera(width, height, 0, 200, -800);
			if( options.dualView ) {
				cameras.leftcamera = new Creator3D.createCamera(width, height, 25, 200, -800);
				cameras.rightcamera = new Creator3D.createCamera(width, height, -25, 200, -800);
				garbageCollector.push(cameras.rightcamera);
			}
			
			threeMainObj.renderer = new THREE.WebGLRenderer();
			threeMainObj.renderer.setSize(width, height);
			

			if( options.dualView ) {
				threeMainObj.renderer.autoClear = false;
			}

			$container.append(threeMainObj.renderer.domElement);

			threeMainObj.controls = new Creator3D.createControls(cameras.leftcamera, false, false, false);
			dnd.projector = new THREE.Projector();

			threeMainObj.scene = new THREE.Scene();
			threeMainObj.scene.add(cameras.leftcamera);
			threeMainObj.scene.fog = new THREE.Fog( 0xffffff, 0.5, 40000 );
			cameras.leftcamera.lookAt(threeMainObj.scene.position);
			if( options.dualView ) {
				threeMainObj.scene.add(cameras.rightcamera);
				cameras.rightcamera.lookAt(threeMainObj.scene.position);
			}

			threeMainObj.renderer.domElement.addEventListener( 'mousemove', onDocumentMouseMove, false );
			threeMainObj.renderer.domElement.addEventListener( 'mousedown', onDocumentMouseDown, false );
			threeMainObj.renderer.domElement.addEventListener( 'mouseup', onDocumentMouseUp, false );

			garbageCollector.push(cameras.leftcamera);
			garbageCollector.push(threeMainObj.renderer);
			garbageCollector.push(threeMainObj.controls);
			garbageCollector.push(threeMainObj.scene.fog);
			garbageCollector.push(threeMainObj.scene);
			garbageCollector.push(dnd.projector);
		},
		initStats = function(){
			threeMainObj.stats = new Stats();
			threeMainObj.stats.domElement.style.top = '0px';
			threeMainObj.stats.domElement.style.position = 'absolute';
			container.appendChild( threeMainObj.stats.domElement );

			garbageCollector.push(threeMainObj.stats);
		},
		initWorld = function(){
			var planeGeo = new THREE.PlaneGeometry(game.getMap().x, game.getMap().z, 10, 10),
				grassTexture = new THREE.ImageUtils.loadTexture("img/textures/grass.jpg"),
				planeMat;

			grassTexture.wrapS = grassTexture.wrapT = THREE.RepeatWrapping;
			grassTexture.repeat.set( 10, 10 );
			planeMat = new THREE.MeshLambertMaterial({
				map:grassTexture,
				shading: THREE.FlatShading,
			    side: THREE.DoubleSide,
			});
			
			objects.world = new THREE.Mesh(planeGeo, planeMat);
			objects.world.rotation.x = -Math.PI/2;
			objects.world.position.z = 10000;
			objects.world.position.y = -500;

			objects.line = initLine(0,0,0);

			threeMainObj.scene.add(objects.world);
			threeMainObj.scene.add(objects.line);

			garbageCollector.push(objects.world);
		},
		initLight = function(){
			objects.light = new THREE.SpotLight( 0xFFFFFF , 1.5);
			objects.light.position.x = 0;
			objects.light.position.y = 15000;
			objects.light.position.z = -600;
			objects.light.shadowCameraFar = 20000;
			threeMainObj.scene.add(objects.light);

			garbageCollector.push(objects.light);
		},
		initLine = function(x,y,z){
			var material = new THREE.LineBasicMaterial({
			        color: 0xCC0000,
			        lineWidth: 15
			    }),
				lineGeometry = new THREE.Geometry();

		    
		    lineGeometry.vertices.push(new THREE.Vector3(0, 0, 0));
		    lineGeometry.vertices.push(new THREE.Vector3(x, y, z));

		    objects.line = new THREE.Line(lineGeometry, material);

		    return objects.line;
		},
		initDnDPlane = function() {
			dnd.dndPlane = new THREE.Mesh( 
				new THREE.PlaneGeometry( 2000, 2000, 8, 8 ), 
				new THREE.MeshBasicMaterial( { color: 0x000000, 
				opacity: 0.25, 
				transparent: true, 
				wireframe: true 
			}));
			dnd.dndPlane.visible = false;
			threeMainObj.scene.add( dnd.dndPlane );

			garbageCollector.push(dnd.dndPlane);
		},
		render = function() {
			threeMainObj.controls.update();
			threeMainObj.renderer.render( threeMainObj.scene, cameras.leftcamera );
		},
		dualViewRender = function() {
			threeMainObj.controls.update();

			cameras.leftcamera.aspect = 0.5 * width / height;
			cameras.rightcamera.aspect = 0.5 * width / height;

			cameras.leftcamera.updateProjectionMatrix();
			cameras.rightcamera.updateProjectionMatrix();

			threeMainObj.renderer.setViewport( 0, 0, width, height );
			threeMainObj.renderer.clear();
			
			// left side
			threeMainObj.renderer.setViewport( 1, 1,   0.5 * width - 2, height - 2 );
			threeMainObj.renderer.render( threeMainObj.scene, cameras.leftcamera );
			
			// right side
			threeMainObj.renderer.setViewport( 0.5 * width + 1, 1,   0.5 * width - 2, height - 2 );
			threeMainObj.renderer.render( threeMainObj.scene, cameras.rightcamera );	
		},
		refreshBallPosition = function(){
			objects.myBall.position.x = 0;
			objects.myBall.position.y = 0;
			objects.myBall.position.z = 0;
			objects.myBall.visible = false;
			threeMainObj.scene.remove(objects.line);
			setTimeout(function(){
				objects.line  = initLine(0, 0, 0);
				threeMainObj.scene.add(objects.line);
				objects.myBall.visible = true;
				MOVABLE = true;
				dnd.mouse.x = 0;
				dnd.mouse.y = - 0;
			},2000);
			
		},
		calcDistance = function() {
			var result,
				vect0;
			
			vect0 = new THREE.Vector3(0, 0, 0);
			result = objects.myBall.position.distanceTo(vect0);
			delete vect0;
			return result;
		},
		deleteObjects = function(id) {
			threeMainObj.scene.remove(objects.balls[id]);
			delete objects.balls[id];
		},
		moveTarget = function(target) {
			if(objects.targets[target.id]){
				objects.targets[target.id].position.x = target.position.x;
				objects.targets[target.id].position.y = target.position.y;
				objects.targets[target.id].position.z = target.position.z;
			}
		},
		animate = function() {
			if(STARTED){
				requestAnimationFrame( animate );
				if( options.dualView ) {
					dualViewRender();
				} else {
					render();
				}
				threeMainObj.stats.update();
			}
		},
		getCurrentCamera = function() {
			if( options.dualView ) {
				if(event.clientX > (window.innerWidth / 2)){
					return cameras.rightcamera;
				}
			}
			return cameras.leftcamera;
		},
		loaderCallBack = function() {
			$gameLoader.find('#loaderCase').hide();
			if(loadEndCallback) loadEndCallback();
			$gameLoader.find('#waitingCase').show();
		},
		checkVisibility = function(position) {
			if(position.z < 20000){
				return true;
			}
			return false;
		},
		onWindowResize = function() {
			cameras.leftcamera.aspect = window.innerWidth / window.innerHeight;
			cameras.leftcamera.updateProjectionMatrix();

			threeMainObj.renderer.setSize( window.innerWidth, window.innerHeight );
		},
		onDocumentMouseUp = function( event ) {
			if(!STARTED || !MOVABLE){
				return 0;
			}
			var power;
			threeMainObj.controls.enabled = true;

			if ( dnd.INTERSECTED ) {
				power = calcDistance();
				if(power > 0){
					shotFunction(power, objects.myBall.position);
					MOVABLE = false;
					event.preventDefault();

					dnd.dndPlane.position.copy( dnd.INTERSECTED.position );
					dnd.SELECTED = null;
					refreshBallPosition();
				}
			}

			$container.css('cursor', 'auto');
		},
		onDocumentMouseMove = function( event ) {
			dnd.mouse.x = ( event.clientX / window.innerWidth ) * 2 - 1;
			dnd.mouse.y = - ( event.clientY / window.innerHeight ) * 2 + 1;

			var currentCamera,
				vector,
				raycaster,
				intersects,
				posNorm;

			event.preventDefault();
			
			currentCamera = getCurrentCamera();

			vector = new THREE.Vector3( dnd.mouse.x, dnd.mouse.y, 0.5 );
			dnd.projector.unprojectVector( vector, currentCamera );

			raycaster = new THREE.Raycaster( currentCamera.position, vector.sub( currentCamera.position ).normalize() );
			intersects = raycaster.intersectObjects( [objects.myBall] );

			if ( dnd.SELECTED ) {
				intersects = raycaster.intersectObject( dnd.dndPlane );
				posNorm = intersects[ 0 ].point.sub( dnd.offset );
				if(STARTED || MOVABLE){
					if(posNorm.y < 0){
						dnd.SELECTED.position.x = posNorm.x;
						dnd.SELECTED.position.y = posNorm.y;
						dnd.SELECTED.position.z = posNorm.y*4;
						threeMainObj.scene.remove(objects.line);
						objects.line  = initLine(posNorm.x, posNorm.y, posNorm.y*4)
						threeMainObj.scene.add(objects.line);
					}
				}
				return;
			}

			if ( intersects.length > 0 ) {
				if ( dnd.INTERSECTED != intersects[ 0 ].object ) {
					dnd.INTERSECTED = intersects[ 0 ].object;
					dnd.dndPlane.position.copy( dnd.INTERSECTED.position );
					dnd.dndPlane.lookAt( currentCamera.position );
				}
				$container.css('cursor', 'pointer');
			} else {
				dnd.INTERSECTED = null;
				$container.css('cursor', 'auto');
			}

			delete vector;
			delete raycaster;
		},
		onDocumentMouseDown = function( event ) {
			if(!STARTED || !MOVABLE){
				return 0;
			}
			var currentCamera,
				vector,
				raycaster,
				intersects;
			event.preventDefault();
			currentCamera = getCurrentCamera();

			threeMainObj.controls.enabled = false;
			vector = new THREE.Vector3( dnd.mouse.x, dnd.mouse.y, 0.5 );
			dnd.projector.unprojectVector( vector, currentCamera );
			raycaster = new THREE.Raycaster( currentCamera.position, vector.sub( currentCamera.position ).normalize() );
			intersects = raycaster.intersectObjects( [objects.myBall] );
			if ( intersects.length > 0 ) {
				dnd.SELECTED = intersects[ 0 ].object;
				intersects = raycaster.intersectObject( dnd.dndPlane );
				dnd.offset.copy( intersects[ 0 ].point ).sub( dnd.dndPlane.position );
				$container.css('cursor', 'move');
			};
			
			delete vector;
			delete raycaster;
		},
		clearGarbageCollector = function( event ) {
			for(key in garbageCollector){
				delete garbageCollector[key];
			}
			if(objects.line) delete objects.line;
			delete garbageCollector;
		},
		clearBallsObjects = function( event ) {
			for(key in objects.balls){
				delete objects.balls[key];
			}
			delete objects.balls;
		},
		clearTargetsObjects = function( event ) {
			for(key in objects.targets){
				delete objects.targets[key];
			}
			delete objects.targets;
		};
	//public methods
	this.startGame = function(value){
		$gameLoader.hide();
		STARTED = true;
		MOVABLE = true;
		game.timer.start(value.delay, game.score.show);
		animate();
	};
	
	this.endGame = function(){
		STARTED = false;
		MOVABLE = false;
		clearGarbageCollector();
		clearBallsObjects();
		clearTargetsObjects();
		$container.empty();
	};
	
	this.setShadows = function(val){
		options.shadows = val;
		objects.light.castShadow = val;

		threeMainObj.renderer.shadowMapEnabled = val;
		threeMainObj.renderer.shadowMapSoft = val;
		objects.world.receiveShadow = val;
		objects.myBall.castShadow = val;
		objects.myBall.receiveShadow = val;
		for(key in objects.balls){
			objects.balls[key].castShadow = val;
			objects.balls[key].receiveShadow = val;
		}
	};

	this.targetAction = function(target){
		var obj;
		switch(target.type){
			case targetType.CREATE:
				obj = Creator3D.createTarget(target, options.targetRadius, options.targetQ);
				objects.targets[target.id] = obj;
				threeMainObj.scene.add(obj);
				break;
			case targetType.MOVE:
				moveTarget(target);
				break;
			case targetType.DESTROY:
				if(objects.targets[target.id]){
					threeMainObj.scene.remove(objects.targets[target.id]);
					delete objects.targets[target.id];
				}
				break;
		};
	};

	this.drawBalls = function(_balls){
		var i, ball,
			len = _balls.length;

		for(i = 0; i < len; i++){
			if(objects.balls[_balls[i].id]){
				if(_balls[i].type == ballType.MOVE){
					if(checkVisibility(_balls[i].position)){
						objects.balls[_balls[i].id].position.x = _balls[i].position.x;
						objects.balls[_balls[i].id].position.y = _balls[i].position.y;
						objects.balls[_balls[i].id].position.z = _balls[i].position.z;
					} else {
						deleteObjects(_balls[i].id);
					}
				} else if(_balls[i].type == ballType.DESTROY){
					deleteObjects(_balls[i].id);
				}
			} else {
				if(_balls[i].type == ballType.CREATE){
					ball = Creator3D.createBall(_balls[i].color, options.ballRadius, options.ballQ);
					ball.position.x = _balls[i].position.x;
					ball.position.y = _balls[i].position.y;
					ball.position.z = _balls[i].position.z;

					ball.castShadow = options.shadows;
					ball.receiveShadow = options.shadows;

					objects.balls[_balls[i].id] = ball;
					threeMainObj.scene.add(ball);
				}
			}
		}
	};

	init();
	render();
	loaderCallBack();
};