let menu;
const reactives = [];
function closeMenu(e) {
	e.classList.remove(['open']);
}
function openMenu(e) { 
	e.classList.add(['open']);
}
function isOpen(e) { 
	return e.classList.contains('open');
}

function toggleMenu() {
	if (isOpen(menu)) {

		reactives.forEach(closeMenu);
		closeMenu(menu);
	} else { 
		console.log(reactives);
		reactives.forEach(openMenu);
		openMenu(menu);
	}
}

document.addEventListener('DOMContentLoaded', function() {
    menu = document.getElementById('menu');

	if (window.innerWidth > 900) {

		reactives.forEach(openMenu);
		openMenu(menu);
		
		// Add animation delay after first open
		setTimeout(() => menu.style.transition = '0.25s');
	} else {
		menu.style.transition = '0.25s'
	}

    document.addEventListener('click', function(e) {
        if (isOpen(menu) && !e.target.matches('.nav, .nav *, .menuItem, .menuItem *, .menuBtn, .menuBtn *')) {
			reactives.forEach(closeMenu);
            closeMenu(menu);
        }
    });

	document.querySelectorAll('#reactive').forEach(elem => {
		console.log(elem);
		reactives.push(elem);
	});

	document.addEventListener('scroll', function() {
		setTimeout(() => {
			reactives.forEach(closeMenu);
			closeMenu(menu);
		}, 150);
	})
});