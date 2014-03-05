var ballType = {
	CREATE: 0,
	MOVE: 1,
	DESTROY: 2
};

var targetType = {
	CREATE: 1,
	MOVE: 2,
	DESTROY: 3
};

var Creator3D = {
	createCamera : function(width, height, x, y , z){
		//private members / methods
		var VIEW_ANGLE = 70,
		    ASPECT = width / height,
		    NEAR = 1,
		    FAR = 20000,
			init = function(){
				var camera = new THREE.PerspectiveCamera(  VIEW_ANGLE,
			                    ASPECT,
			                    NEAR,
			                    FAR  );
				camera.position.x = x;
				camera.position.y = y;
				camera.position.z = z;

				return camera;
			};
		//public methods

		return init();
	},
	createControls : function(camera, noZoomArg, noPanArg, staticMovingArg){
		//private members / methods
		var noZoom = noZoomArg || false,
		    noPan = noPanArg || false,
		    staticMoving = staticMovingArg || false,
			init = function(){
				var controls = new THREE.TrackballControls( camera );
				controls.rotateSpeed = 0;
				controls.zoomSpeed = 0;
				controls.panSpeed = 0;
				controls.noZoom = false;
				controls.noPan = false;
				controls.staticMoving = false;
				controls.dynamicDampingFactor = 0.3;

				return controls;
			};
		//public methods

		return init();
	},
	createTarget : function(target, radius, quality) {
		var targetObj,
			planeGeo,
			grassTexture,
			planeMat;

		circleGeo = new THREE.CircleGeometry(radius, quality);

		targetTexture = new THREE.ImageUtils.loadTexture("img/textures/target.png");

		circleMat = new THREE.MeshLambertMaterial({
			map:targetTexture,
		    side: THREE.DoubleSide,
		});

		targetObj = new THREE.Mesh(circleGeo, circleMat);

		targetObj.position.x = target.position.x;
		targetObj.position.y = target.position.y;
		targetObj.position.z = target.position.z;

		return targetObj;
	},
	createBall : function(hex, radius, quality){
		var sphereMaterial = new THREE.MeshLambertMaterial({ color: hex }),
			Ball;

		Ball = new THREE.Mesh(
		   new THREE.SphereGeometry(radius, quality, quality),
		   sphereMaterial);

		return Ball;
	}
};


