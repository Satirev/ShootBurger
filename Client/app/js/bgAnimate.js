var BgAnimate = function() {
	var camera,
		scene,
		renderer,
		controls,
		particlesTotal = 256,
		positions = [],
		objects = [],
		current = 0,
		loaded = 0,
		stop = false,
		sprites = [],
		spritesSrc = ['img/sprite_red.png', 'img/sprite_green.png', 'img/sprite_yellow.png', 'img/sprite_blue.png'];

	init();

	function init() {
		camera = new THREE.PerspectiveCamera(75, window.innerWidth/ window.innerHeight, 1, 5000);
		camera.position.set(600, 400, 1500);
		camera.lookAt(new THREE.Vector3());

		scene = new THREE.Scene();

		for(var i = 0; i < 4; i++) {
			var sprite = document.createElement('img');
			sprites.push(sprite);
			sprites[i].addEventListener('load', function(event) {
				loaded++;
				if (loaded > 3) {
					insertBalls();
				}
			}, false);
			sprites[i].src = spritesSrc[i];
		}
		
		var insertBalls = function() {
			for(var i = 0, j = 0; i < particlesTotal; i++, j += 3) {
				var canvas = document.createElement('canvas'),
					context = canvas.getContext('2d'),
					current_sprite = sprites[Math.floor(Math.random() * 10) % 4],
					object = new THREE.CSS3DSprite(canvas);

				context.drawImage(current_sprite, 0, 0);
				object.position.x = Math.random() * 4000 - 2000;
				object.position.y = Math.random() * 4000 - 2000;
				object.position.z = Math.random() * 4000 - 2000;
				scene.add(object);

				objects.push(object);
			}
			transition();
		};

		// Plane
		var amountX = 16,
			amountZ = 32,
			separation = 150,
			offsetX = ((amountX - 1) * separation) / 2,
			offsetZ = ((amountZ - 1) * separation) / 2;

		for(var i = 0; i < particlesTotal; i++) {
			var x = (i % amountX) * separation,
				z = Math.floor(i / amountX) * separation,
				y = (Math.sin(x * 0.5) + Math.sin(z * 0.5)) * 200;

			positions.push(x - offsetX, y, z - offsetZ);
		}

		// Cube
		var amount = 8,
			separation = 150,
			offset = ((amount - 1) * separation) / 2;

		for(var i = 0; i < particlesTotal; i++) {
			var x = (i % amount) * separation,
				y = Math.floor((i / amount) % amount) * separation,
				z = Math.floor(i / (amount * amount)) * separation;

			positions.push(x - offset, y - offset, z - offset);
		}

		// Random
		for(var i = 0; i < particlesTotal; i++) {
			positions.push(Math.random() * 4000 - 2000, Math.random() * 4000 - 2000, Math.random() * 4000 - 2000);
		}

		// Sphere
		var radius = 750;

		for(var i = 0; i < particlesTotal; i++) {
			var phi = Math.acos(-1 + (2 * i) / particlesTotal),
				theta = Math.sqrt(particlesTotal * Math.PI) * phi;

			positions.push(radius * Math.cos(theta) * Math.sin(phi), radius	* Math.sin(theta) * Math.sin(phi), radius * Math.cos(phi));
		}

		//
		renderer = new THREE.CSS3DRenderer();
		renderer.setSize(window.innerWidth, window.innerHeight);
		renderer.domElement.style.position = 'absolute';
		document.getElementById('bgContainer').appendChild(renderer.domElement);

		controls = new THREE.TrackballControls(camera, renderer.domElement);
		controls.rotateSpeed = 0.5;

		window.addEventListener('resize', onWindowResize, false);
	};

	function onWindowResize() {
		camera.aspect = window.innerWidth / window.innerHeight;
		camera.updateProjectionMatrix();

		renderer.setSize(window.innerWidth, window.innerHeight);
	};

	function transition() {
		var offset = current * particlesTotal * 3,
			duration = 2000;

		for(var i = 0, j = offset; i < particlesTotal; i++, j += 3) {
			var object = objects[i];

			new TWEEN.Tween(object.position).to({
				x : positions[j],
				y : positions[j + 1],
				z : positions[j + 2]
			}, Math.random() * duration + duration).easing(TWEEN.Easing.Exponential.InOut).start();
		}

		new TWEEN.Tween(this).to({}, duration * 3).onComplete(transition).start();

		current = (current + 1) % 4;
	}

	function animate() {
		if (!stop) {
			requestAnimationFrame(animate);

			TWEEN.update();
			controls.update();

			var time = performance.now();
			for(var i = 0, l = objects.length; i < l; i++) {
				var object = objects[i];
				var scale = Math
						.sin((Math.floor(object.position.x) + time) * 0.002) * 0.3 + 1;
				object.scale.set(scale, scale, scale);
			}
			renderer.render(scene, camera);
		}
	}

	this.startAnimate = function() {
		stop = false;
		animate();
	};

	this.stop = function() {
		stop = true;
	};
};