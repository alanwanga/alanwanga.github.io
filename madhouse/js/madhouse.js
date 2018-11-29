function toggle(id){
  var _this = document.getElementById(id);        
  if($(_this).css("display") == "none"){
	var x = document.getElementsByClassName("tl-body");
	for (var i = 0; i < x.length; i++) {
		$(x[i]).slideUp();
	}
    $(_this).slideDown();
  }else{
    $(_this).slideUp();
  }
  return false;     
};
///////////////////////////////////////////////////
$(document).ready(function() {
  $(document).on( 'click','#filterOptions li a', function() {
    // fetch the class of the clicked item
    var ourClass = $(this).attr('class');
    
    // reset the active class on all the buttons
    $('#filterOptions li').removeClass('active');
    // update the active state on our clicked button
    $(this).parent().addClass('active');
    
    if(ourClass == 'all') {
      // show all our items
      $('#ourHolder').children('li.item').slideDown();  
    }
    else {
      // hide all elements that don't share ourClass
      $('#ourHolder').children('li.item:not(.' + ourClass + ')').slideUp();
      // show all elements that do share ourClass
      $('#ourHolder').children('li.item.' + ourClass).slideDown();
    }
    return false;
  });
});
///////////////////////////////////////////////////
window.onload = function() { init() };
var public_spreadsheet_url = 'https://docs.google.com/spreadsheet/pub?hl=en_US&hl=en_US&key=1YCdZGk9QSNsTKJKZTpZABEvus5qMCNtD4LRMyqtTza0&output=html';

String.format = function() {
      var s = arguments[0];
      for (var i = 0; i < arguments.length - 1; i++) {       
          var reg = new RegExp("\\{" + i + "\\}", "gm");             
          s = s.replace(reg, arguments[i + 1]);
      }
      return s;
  }
function init() {
  Tabletop.init( { key: public_spreadsheet_url,
                   callback: madhouse,
                   simpleSheet: true } );
}

function madhouse(data){
  genFilter(data);
  showInfo(data);
};

function genFilter(data){
  name_set = new Set()
  for (index in data){
    name_set.add(data[index]['Author'])
  }
  if (name_set.size > 0){
    filter = document.getElementById('filterOptions')
    res = ['<li class="active"><a href="#" class="all">All</a></li>']
    name_set.forEach(function(name){
      res.push(String.format('<li><a href="#" class="{0}">{1}</a></li>',name,name))
    })
    filter.innerHTML = res.join('\n')
  }
}
function showInfo(data) {
  // sort by date
  data.sort(function(a, b){return new Date(b['Event Time (YYYY/MM/DD)'])- new Date(a['Event Time (YYYY/MM/DD)'])});
  timeline = document.getElementById('ourHolder');

  for(var index in data){
    time = new Date(data[index]['Event Time (YYYY/MM/DD)'])
    year = time.toDateString().split(' ')[3]
    month = time.toDateString().split(' ')[1]
    if (document.getElementById(year) == null){
      tldate = document.createElement('li');
      tldate.innerHTML = String.format('<div class="tldate" id="{0}">{1}</div>',year,year);
      timeline.appendChild(tldate);
    }
    doc = document.createElement('li');
    doc.classList.add('item',data[index]['Author'])
    if (index %2 == 1){
      doc.classList.add('timeline-inverted');
    }
    doc.innerHTML = String.format(
      `<div class="tl-circ"></div>
        <div class="timeline-panel" onclick="toggle(\'t{0}\');" style="cursor: pointer; cursor: hand;">
          <div class="tl-heading">
            <h4>{1}</h4>
            <small class="text-muted"><i class="glyphicon glyphicon-user"></i>{2}</small>
          </div>
          <div class="tl-body" id="t{3}" style="font-family:Microsoft JhengHei;display:none;">
            <br />
            <p>{4}</p>
            <p><img src="{5}" onerror="this.style.display='none'" /></p>
            <br />
          </div>
          <small class="text-muted"><i class="glyphicon glyphicon-time"></i>{6}</small>
        </div>
      </li>`,
      index,
      data[index]['Title'],
      data[index]['Author'],
      index,
      data[index]['Content'].replace(/\n/g,"</p><p>").replace(/<p><\/p>/g,"<br />"),
      data[index]['Image URL'],
      month+' '+year);

    timeline.appendChild(doc)
    //console.log(data[index]['內容'].replace(/\n/g,"</p><p>"));
  }
}