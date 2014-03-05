temp

	// function animate(t) {
 //        // spin the camera in a circle
 //        camera.position.x = Math.sin(t/1000)*300;
 //        camera.position.y = 150;
 //        camera.position.z = Math.cos(t/1000)*300;
 //        // you need to update lookAt every frame
 //        camera.lookAt(scene.position);
 //        // renderer automatically clears unless autoClear = false
 //        renderer.render(scene, camera);
 //        window.requestAnimationFrame(animate, renderer.domElement);
 //      };

 container = document.getElementById( 'canvasContainer' );
	var mouse = new THREE.Vector2(),
		offset = new THREE.Vector3(),
		INTERSECTED, SELECTED,
		stats;



	stats = new Stats();
	stats.domElement.style.top = '0px';
	stats.domElement.style.position = 'absolute';
	container.appendChild( stats.domElement );

	function v(x,y,z){ 
        return new THREE.Vertex(new THREE.Vector3(x,y,z)); 
      }
      
      var lineGeo = new THREE.Geometry();
      lineGeo.vertices.push(
        v(-10000, 0, 0), v(10000, 0, 0),
        v(0, -10000, 0), v(0, 10000, 0),
        v(0, 0, -10000), v(0, 0, 10000)
      );
      var lineMat1 = new THREE.LineBasicMaterial({
        color: 0xFF0000, lineWidth: 1});
      // var lineMat2 = new THREE.LineBasicMaterial({
      //   color: 0x00FF00, lineWidth: 1});
      // var lineMat3 = new THREE.LineBasicMaterial({
      //   color: 0x0000FF, lineWidth: 1});
      var line = new THREE.Line(lineGeo, lineMat1);
      line.type = THREE.Lines;
      // scene.add(line);


	nonVisiableplane = new THREE.Mesh( new THREE.PlaneGeometry( 2000, 2000, 8, 8 ), new THREE.MeshBasicMaterial( { color: 0x000000, opacity: 0.25, transparent: true, wireframe: true } ) );
	nonVisiableplane.visible = false;
	scene.add( nonVisiableplane );

    projector = new THREE.Projector();

	camera.lookAt(scene.position);

    function onDocumentMouseMove( event ) {
		event.preventDefault();

		mouse.x = ( event.clientX / window.innerWidth ) * 2 - 1;
		mouse.y = - ( event.clientY / window.innerHeight ) * 2 + 1;

		//

		var vector = new THREE.Vector3( mouse.x, mouse.y, 0.5 );
		projector.unprojectVector( vector, camera );

		var raycaster = new THREE.Raycaster( camera.position, vector.sub( camera.position ).normalize() );


		if ( SELECTED ) {
			var intersects = raycaster.intersectObject( nonVisiableplane );
			SELECTED.position.copy( intersects[ 0 ].point.sub( offset ) );
			return;

		}


		var intersects = raycaster.intersectObjects( objects );

		if ( intersects.length > 0 ) {

			if ( INTERSECTED != intersects[ 0 ].object ) {

				if ( INTERSECTED ) INTERSECTED.material.color.setHex( INTERSECTED.currentHex );

				INTERSECTED = intersects[ 0 ].object;
				INTERSECTED.currentHex = INTERSECTED.material.color.getHex();

				nonVisiableplane.position.copy( INTERSECTED.position );
				nonVisiableplane.lookAt( camera.position );

			}

			$container.css('cursor', 'pointer');

		} else {

			if ( INTERSECTED ) INTERSECTED.material.color.setHex( INTERSECTED.currentHex );

			INTERSECTED = null;

			$container.css('cursor', 'auto');

		}

	}

	function onDocumentMouseDown( event ) {

		event.preventDefault();

		var vector = new THREE.Vector3( mouse.x, mouse.y, 0.5 );
		projector.unprojectVector( vector, camera );

		var raycaster = new THREE.Raycaster( camera.position, vector.sub( camera.position ).normalize() );

		var intersects = raycaster.intersectObjects( objects );

		if ( intersects.length > 0 ) {

			controls.enabled = false;
 
			SELECTED = intersects[ 0 ].object;
			var intersects = raycaster.intersectObject( nonVisiableplane );
			offset.copy( intersects[ 0 ].point ).sub( nonVisiableplane.position );

			$container.css('cursor', 'move');
		}

	}

	function onDocumentMouseUp( event ) {

		event.preventDefault();

		controls.enabled = true;

		if ( INTERSECTED ) {

			nonVisiableplane.position.copy( INTERSECTED.position );

			SELECTED = null;

		}

		$container.css('cursor', 'auto');

	}

	function animate() {

		requestAnimationFrame( animate );

		render();

		stats.update();

	}

	function render() {

		controls.update();

		renderer.render( scene, camera );

	}

    renderer.domElement.addEventListener( 'mousemove', onDocumentMouseMove, false );
	renderer.domElement.addEventListener( 'mousedown', onDocumentMouseDown, false );
	renderer.domElement.addEventListener( 'mouseup', onDocumentMouseUp, false );
      // animate(new Date().getTime());

      animate();

      		if ( SELECTED ) {
			// var intersects = raycaster.intersectObject( nonVisiableplane );
			console.log('jestem tutaj', vector.sub( camera.position ).normalize());
			var normPos = vector.sub( camera.position ).normalize();

			SELECTED.position.x = normPos.x;
			SELECTED.position.y = normPos.y;

			return;

		}