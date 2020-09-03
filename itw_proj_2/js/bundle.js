$(document).ready(function() {
  // Smooth scrolling nav
  $('a').click(function(e) {
    if($(this).data('smooth')) {
      e.preventDefault();
      
      $('html, body').animate({
        scrollTop: $('#' + $(this).data('smooth')).offset().top - $('#nav').height() - 50
      }, 500);
    }
  })

  // Toggling menu on mobile
  $('.mobile-toggle').click(function(e) {
    e.preventDefault();
    if($('#nav ul').is(':visible')){
      $('#nav ul').slideUp(400);
    } else {
      $('#nav ul').slideDown(400);
    }
  });

  // Experience tabs functionality
  $('#experience_nav a').click(function(e){
    e.preventDefault();
    $('#experience_nav a').removeClass('active');
    $(this).addClass('active');

    $('#experience .tabs .tab').removeClass('active');
    $('#experience .tabs #' + $(this).data('tab-nav')).addClass('active');
  });

  // Menu fixing
  $(window).scroll(function() {
    if($(this).scrollTop() > 0) {
      $('#nav').addClass('fixed');
    } else {
      $('#nav').removeClass('fixed');
    }
  });

  $(window).resize(function() {
    if($(window).width() >= 768 && $('#nav ul').css('display') !== 'flex') {
      $('#nav ul').css({ display: 'flex' });
    }
  });
});
