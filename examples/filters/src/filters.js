/*
 * Copyright 2016 Canonical Ltd.
 *
 * This file is part of unity-js-scopes.
 *
 * unity-js-scopes is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * unity-js-scopes is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

var scopes = require('unity-js-scopes')

var CATEGORY_TEMPLATE =
    {
  "schema-version": 1,
  "template": {
    "category-layout": "grid",
    "card-layout": "horizontal",
    "card-size": "medium"
  },
  "components": {
    "title": "title",
    "art" : {
      "field": "art"
    },
    "subtitle": "subtitle",
    "attributes": {
      "field": "attributes",
      "max-count": 2
    }
  }
}

var books = [];

function book(titlev, formatv, authorv, pricev, ratingv, departmentv, categoryv, synopsisv, artv)
{
  return {
    title: titlev,
    format: formatv,
    author: authorv,
    price: pricev,
    rating: ratingv,
    department: departmentv,
    category: categoryv,
    synopsis: synopsisv,
    art: artv,
  }
}

books.push(book(
             "Your Heart is a Muscle the Size of a Fist",
             "hardback",
             "Sunil Yapa",
             14.99,
             3,
             "fiction",
             "bestseller",
             "A heart-stopping debut about protest and riot ...1999. Victor, homeless after a family tragedy, finds himself pounding the streets of Seattle with little meaning or purpose. He is the estranged son of the police chief of the city, and today his father is in charge of one of the largest protests in the history of Western democracy. But in a matter of hours reality will become a nightmare. Hordes of protesters - from all sections of society - will test the patience of the city's police force, and lives will be altered forever: two armed police officers will struggle to keep calm amid the threat of violence; a protester with a murderous past will make an unforgivable mistake; and a delegate from Sri Lanka will do whatever it takes to make it through the crowd to a meeting - a meeting that could dramatically change the fate of his country. In amongst the fray, Victor and his father are heading for a collision too. Your Heart is a Muscle the Size of a Fist, set during the World Trade Organization protests, is a deeply charged novel showcasing a distinct and exciting new literary voice.",
             "1.jpg"
             )
           );

books.push(book(
             "Gold Fame Citrus",
             "hardback",
             "Claire Vaye Watkins",
             16.99,
             4,
             "fiction",
             "book of the month",
             "Desert sands have laid waste to the south-west of America. Las Vegas is buried. California - and anyone still there - is stranded. Any way out is severely restricted. But Luz and Ray are not leaving. They survive on water rations, black market fruit and each other's need. Luz needs Ray, and Ray must be needed. But then they cross paths with a mysterious child, and the thirst for a better future begins. It's said there's a man on the edge of the Dune Sea. He leads a camp of believers. He can find water. Venturing into this dry heart of darkness, Luz thinks she has found their saviour. For the will to survive taps hidden powers; and the needed, and the needy, will exploit it. Like Margaret Atwood, Claire Vaye Watkins uses dystopia to traverse the scarred frontier of the heart, exploring the myths we tell about others and ourselves. In her bare and brilliant prose, nature and human nature, conspiracy and cult, motherhood and manhood are played out across the vast, implacable desert.",
             "2.jpg"
             )
           );

books.push(book(
             "Love + Hate: Stories and Essay",
             "paperback",
             "Hanif Kureishi",
             9.99,
             5,
             "fiction",
             "bestseller",
             "Hate skews reality even more than love. In the story of a Pakistani woman who has begun a new life in Paris, an essay about the writing of Kureishi's acclaimed film Le Week-End, and an account of Kafka's relationship with his father, readers will find Kureishi also exploring the topics that he continues to make new, and make his own: growing up and growing old; betrayal and loyalty; imagination and repression; marriage and fatherhood. The collection ends with a bravura piece of very personal reportage about the conman who stole Kureishi's life savings - a man who provoked both admiration and disgust, obsession and revulsion, love and hate.",
             "3.jpg"
             )
           );

books.push(book(
             "The Book of Speculation",
             "audiobook",
             "Erika Swyler",
             12.99,
             4,
             "fiction",
             "bestseller",
             "Simon Watson lives alone on the Long Island Sound in his family home, a house perched on the edge of a cliff that is slowly crumbling into the sea.  His parents are long dead, his mother having drowned in the water his house overlooks. His younger sister, Enola, works for a travelling carnival and seldom calls. On a day in late June, Simon receives a mysterious book from an antiquarian bookseller; it has been sent to him because it is inscribed with the name Verona Bonn, Simon's grandmother. The book tells the story of two doomed lovers who were part of a travelling circus more than two hundred years ago. The paper crackles with age as Simon turns the yellowed pages filled with notes and sketches. He is fascinated, yet as he reads Simon becomes increasingly unnerved. Why do so many women in his family drown on 24th July? And could Enola, who has suddenly turned up at home for the first time in years, risk the same terrible fate? As 24th July draws ever closer, Simon must unlock the mysteries of the book, and decode his family history, before it's too late.",
             "4.jpg"
             )
           );

books.push(book(
             "Rush Oh!",
             "hardback",
             "Shirley Barrett",
             14.99,
             4,
             "fiction",
             "bestseller",
             "When Mary Davidson, the eldest daughter of a whaling family in Eden, New South Wales, sets out to chronicle the particularly difficult season of 1908, the story she tells is poignant and hilarious, filled with drama and misadventure. It's a season marked not only by the sparsity of whales and the vagaries of weather, but also by the arrival of John Beck, an itinerant whaleman with a murky past, on whom Mary promptly develops an all-consuming crush. But hers is not the only romance to blossom amidst the blubber ...Swinging from Mary's hopes and disappointments, both domestic and romantic, to the challenges that beset their tiny whaling operation, Rush Oh! is a celebration of an extraordinary episode in Australian history when a family of whalers formed a fond, unique alliance with a pod of frisky killer whales - and in particular, a killer whale named Tom.",
             "5.jpg"
             )
           );

books.push(book(
             "The High Mountains of Portugal",
             "hardback",
             "Yann Martel",
             18.99,
             3,
             "fiction",
             "special edition",
             "Lost in Portugal. Lost to grief. With nothing but a chimpanzee. The extraordinary new novel from the author of Life of Pi. In Lisbon in 1904, a young man named Tomas discovers an old journal. It hints at the location of an extraordinary artefact that - if it exists - would redefine history. Travelling in one of Europe's earliest automobiles, he sets out in search of this treasure. Some thirty-five years later, a Portuguese pathologist finds himself at the centre of a murder mystery. Fifty years on, a Canadian senator takes refuge in northern Portugal, grieving the loss of his beloved wife. But he comes to his ancestral village with an unusual companion: a chimpanzee. Three stories. Three broken hearts. One exploration: what is a life without stories? The High Mountains of Portugal takes the reader on a road trip through Portugal in the last century - and through the human soul.",
             "6.jpg"
             )
           );

books.push(book(
             "Rebel of the Sands",
             "audiobook",
             "Alwyn Hamilton",
             7.99,
             3,
             "fiction",
             "recommended",
             "Sold immediately at auction across the world, this phenomenal novel is the first in a trilogy packed with shooting contests, train robberies, festivals under the stars, powerful Djinni magic and an electrifying love story. This promises to be a global super lead. Tell me that and we'll go.  Right now. Save ourselves and leave this place to burn. Tell me that's how you want your story to go and we'll write it straight across the sand.' Dustwalk is Amani's home. The desert sand is in her bones. But she wants to escape. More than a want. A need. Then a foreigner with no name turns up to save her life, and with him the chance to run. But to where? The desert plains are full of danger. Sand and blood are swirling, and the Sultan's enemies are on the rise.",
             "7.jpg"
             )
           );

books.push(book(
             "More of Me",
             "paperback",
             "Kathryn Evans",
             6.99,
             4,
             "fiction",
             "special edition",
             "Teva seems normal. But at home she hides an impossible secret: 11 other Tevas. Because once a year, Teva splits into two, leaving a younger version of herself stuck at the same age, forced to watch the new Teva taking over her life. But at 16, Teva's had enough. She's going to fight for her future - even if that means fighting herself. Imagine all your friends growing up, moving on, and you being stuck in one year of your life...More of Me is an incredible, unforgettable story of identity, friendship, love and sacrifice.",
             "8.jpg"
             )
           );

books.push(book(
             "How Hard Can Love be?",
             "paperback",
             "Holly Bourne",
             7.99,
             4,
             "fiction",
             "recommended",
             "Sorry, no synopsis is currently available.",
             "9.jpg"
             )
           );

books.push(book(
             "How Not to Disappear",
             "hardback",
             "Clare Furniss",
             12.99,
             3,
             "fiction",
             "recommended",
             "Our memories are what make us who we are. Some are real. Some are made up. But they are the stories that tell us who we are. Without them we are nobody.Hattie's summer isn't going as planned. Her two best friends have abandoned her: Reuben has run off to Europe to 'find himself' and Kat is in Edinburgh with her new girlfriend. Meanwhile Hattie is stuck babysitting her twin siblings and dealing with endless drama around her mum's wedding.  Oh, and she's also just discovered that she's pregnant with Reuben's baby...Then Gloria, Hattie's great-aunt who no one even knew existed, comes crashing into her life. Gloria's fiercely independent, rather too fond of a gin sling and is in the early stages of dementia. Together the two of them set out on a road trip of self-discovery - Gloria to finally confront the secrets of her past before they are erased from her memory forever and Hattie to face the hard choices that will determine her future...Non Pratt's Trouble meets Thelma and Louise with a touch of Elizabeth is Missing by Emma Healey, Clare Furniss' remarkable How Not To Disappear is an emotional rollercoaster of a novel that will make you laugh and break your heart.",
             "10.jpg"
             )
           );

books.push(book(
             "Front Lines",
             "paperback",
             "Michael Grant",
             7.99,
             2,
             "fiction",
             "recommended",
             "Just when you thought Michael Grant's Gone series had taken us to the darkest limits of his imagination, the evil genius of YA fiction is back to take you to the Front Lines of terror. In the tradition of The Book Thie, Code Name Verity and Between Shades of Gray, Front Lines gives the experience of WWII a new immediacy while playing with the 'what ifs?' of history. It's WWII, but not as you remember it from history lessons! This time the girls aren't stitching socks for the brave boys at the front. Meet Rio Richilin and her friends Frangie Marr and Rainy Schulterman, three of the newest recruits in the US Armed Forces. They stand shoulder to shoulder with the boys from home as they take on Hitler's army. In the face of reluctant colonels and sceptical sergeants, the soldier girls must prove their guts, strength, and resourcefulness as soldiers. Rio has grown up in a world where men don't cry and girls are supposed to care only about 'money and looks'. But she has always known that there is something wrong with this system and something else in her. Far from home and in the battlefields, Rio discovers exactly who she is and what she can accomplish.",
             "11.jpg"
             )
           );

books.push(book(
             "All the Rage",
             "paperback",
             "Courtney Summers",
             17.99,
             5,
             "fiction",
             "special edition",
             "The footsteps stop but the birds are still singing, singing about a girl who wakes up on a dirt road and doesn't know what happened to her the night before...' Romy Grey wears her lipstick like armour, ever since the night she was raped by Kellan Turner, the sheriff's son. Romy refuses to be a victim, but speaking up has cost her everything. No one wants to believe Kellan is not the golden boy they thought he was, and Romy has given up trying to make herself heard. But when another girl goes missing after a party, Romy must decide whether the cost of her silence might be more than she can bear.",
             "12.jpg"
             )
           );

books.push(book(
             "Sticker Dolly Dressing Fashion Designer London Collection",
             "hardback",
             "Fiona Watt",
             6.99,
             2,
             "childrens",
             "recommended",
             "London is one of the great fashion capitals of the world, and this book, with over 350 stickers - including 150 to colour yourself - allows young creatives to research, plan and design their own fashion collections, inspired by the city. With hints and tips on how to choose colours, patterns and shapes that work together.",
             "1.jpg"
             )
           );

books.push(book(
             "Waiting for Callback",
             "paperback",
             "Perdita Cargill",
             6.99,
             3,
             "childrens",
             "recommended",
             "Geek Girl meets Fame meets New Girl in this brilliantly funny new series! When Elektra is discovered by an acting agent, she imagines Oscar glory can't be far away, but instead lurches from one cringe-worthy moment to the next! Just how many times can you be rejected for the part of 'Dead Girl Number Three' without losing hope? And who knew that actors were actually supposed to be multi-lingual, play seven instruments and be trained in a variety of circus skills? Off-stage things aren't going well either - she's fallen out with her best friend, remains firmly in the friend-zone with her crush and her parents are driving her crazy. One way or another, Elektra's life is now spent waiting for the phone to ring - waiting for callback. Can an average girl-next-door like Elektra really make it in the world of luvvies and starlets?",
             "2.jpg"
             )
           );

books.push(book(
             "Anna and the Swallow Man",
             "hardback",
             "Gavriel Savit",
             9.99,
             4,
             "childrens",
             "special edition",
             "Anna and the Swallow Man is a stunning, literary, and wholly original debut novel that tells a new WW2 story. Krakow, 1939, is no place to grow up.  There are a million marching soldiers and a thousand barking dogs. And Anna Lania is just seven years old when the Germans take her father and suddenly, she's alone. Then she meets the Swallow Man. He is a mystery, strange and tall. And like Anna's missing father, he has a gift for languages: Polish, Russian, German, Yiddish, even Bird. When he summons a bright, beautiful swallow down to his hand to stop her from crying, Anna is entranced. Over the course of their travels together, Anna and the Swallow Man will dodge bombs, tame soldiers, and even, despite their better judgement, make a friend. But in a world gone mad, everything can prove dangerous...",
             "3.jpg"
             )
           );

books.push(book(
             "Time Travelling with a Hamster",
             "paperback",
             "Ross Welford",
             16.99,
             3,
             "childrens",
             "bestseller",
             "A truly original debut novel from an extraordinarily talented new voice in children's books. Laugh, cry and wonder at this race-against-time story of a boy who travels back to 1984 to prevent a go-kart accident, and save his father's life...'My dad died twice. Once when he was thirty nine and again four years later when he was twelve. The first time had nothing to do with me. The second time definitely did, but I would never even have been there if it hadn't been for his 'time machine'...\" When Al Chaudhury discovers his late dad's time machine, he finds that going back to the 1980s requires daring and imagination. It also requires lies, theft, burglary, and setting his school on fire. All without losing his pet hamster, Alan Shearer...",
             "4.jpg"
             )
           );

books.push(book(
             "The Long Haul",
             "paperback",
             "Jeff Kinney",
             9.99,
             3,
             "childrens",
             "recommended",
             "A family road trip is supposed to be a lot of fun ...unless, of course, you're the Heffleys. The journey starts off full of promise, then quickly takes several wrong turns. Gas station bathrooms, crazed seagulls, a fender bender, and a runaway pig - not exactly Greg Heffley's idea of a good time. But even the worst road trip can turn into an adventure - and this is one the Heffleys won't soon forget. Zoo-Wee-Mama! Includes exclusive bumper stickers!",
             "5.jpg"
             )
           );

books.push(book(
             "Barry Loser Hates Half Term",
             "audiobook",
             "Jim Smith",
             12.99,
             4,
             "childrens",
             "recommended",
             "This is the seventh book in the brilliant Roald Dahl Funny Prize award-winning series Barry Loser. Suitable for fans of Diary of a Wimpy Kid and Tom Gates. It's only a few days into the half-term holidays and Barry's dad has already had enough of him! He's packing Barry off to Pirate Camp, the same one he used to be sent to every year. Barry's not impressed - he's not a baby anymore, so why should he have to go to a camp for kiddy winkles?  But horrible things are a foot at Pirate Camp - it's been taken over by the villainous Morag, and now its future's in doubt. There's only one thing to do: Barry and his new friends Sally Bottom and Renard Dupont have to uncover the hidden treasure of Mogden Island...Join everyone's favourite Loser on his seventh hilarious adventure!",
             "6.jpg"
             )
           );

books.push(book(
             "The Butterfly Club",
             "paperback",
             "Jacqueline Wilson",
             9.99,
             3,
             "childrens",
             "recommended",
             "Tina is a triplet, but she's always been the odd one out. Her sisters Phil and Maddie are bigger and stronger and better at just about everything.  Luckily, they look after teeny-tiny Tina wherever they go - but when the girls start in scary, super-strict Miss Lovejoy's class, they're split up, and Tina has to fend for herself for the first time. Tina is horrified when she's paired up with angry bully Selma, who nobody wants to be friends with.  But when Miss Lovejoy asks them to help her create a butterfly garden in the school playground, Tina discovers she doesn't always need her sisters - and that there's a lot more to Selma than first meets the eye. This is a beautiful, heartwarming story about friendship, confidence and becoming your own person, from the mega-bestselling author of Tracy Beaker, Hetty Feather and Sleepovers.",
             "7.jpg"
             )
           );

books.push(book(
             "Over 100 Animal Doodles",
             "paperback",
             "Fiona Watt",
             11.99,
             4,
             "childrens",
             "recommended",
             "Lots of simple instructions that will allow children to draw a range of animals with satisfying results. Learn step-by-step, with diagrams that explain how to use simple shapes to create animals - then practise drawing them again and again, creating scenes.",
             "8.jpg"
             )
           );

books.push(book(
             "Confessions of an Imaginary Friend",
             "audiobook",
             "Michelle Cuevas",
             14.99,
             3,
             "childrens",
             "bestseller",
             "Jacques Papier thinks that everyone hates him. After all, teachers ignore him when he raises his hand in class, nobody ever picks him for sports teams, and his sister, Fleur, keeps having to remind their parents to set a place for him at the dinner table. But then Jacques discovers an uncomfortable truth: He is NOT Fleur's brother; he's her imaginary friend! And so begins Jacques' quest for identity ...what do you do when you realise that the only reason you exist is because of someone else's imagination? The whimsical \"autobiography\" of an imaginary friend who doesn't know he's imaginary - perfect for fans of Toy Story, The Imaginary and Moone Boy.",
             "9.jpg"
             )
           );

books.push(book(
             "Shaun the Sheep - the Farmer's Llamas",
             "paperback",
             "Aardman Animations Ltd",
             16.99,
             4,
             "childrens",
             "rook of the month",
             "When a mix-up at the auction leads to a surprise win, the Farmer brings his prize animals - a trio of llamas - home to the farm. Shaun is thrilled, but are the new residents a baaad influence? Based on a one-of, half-hour TV episode, this junior novel includes full-colour stills from the special.",
             "10.jpg"
             )
           );

function match(book, query, department, format, categories, min_price, max_price, rating)
{
  if (department && book.department !== department)
  {
    return false;
  }

  if (format && book.format !== format)
  {
    return false;
  }

  if (categories.length && categories.indexOf(book.category) === -1)
  {
    return false;
  }

  if (book.price < min_price || book.price > max_price)
  {
    return false;
  }

  if (book.rating < rating)
  {
    return false;
  }

  if (query && book.title.indexOf(query) === -1 && book.author.indexOf(query) === -1)
  {
    return false;
  }

  return true;
}

function generate_results(canned_query, reply, book_format, book_categories, min_price, max_price, rating)
{
  var query_string = canned_query.query_string();
  var dept_id = canned_query.department_id();

  var show_single_cat = (dept_id);

  rating = Math.round(rating);

  var count = 0;
  if (show_single_cat) {
    for (var i = 0; i < books.length; i++)
    {
      if (match(books[i], query_string, dept_id, book_format, book_categories, min_price, max_price, rating)) {
        ++count;
      }
    }
  }

  var category_renderer = new scopes.lib.CategoryRenderer(JSON.stringify(CATEGORY_TEMPLATE));
  var cat_single = reply.register_category("all", count + " Books", "", category_renderer);
  var cat_fiction = reply.register_category("fiction", "Fiction", "", category_renderer);
  var cat_children = reply.register_category("childrens", "Children", "", category_renderer);

  for (var i = 0; i < books.length; i++)
  {
    book = books[i];
    if (match(book, query_string, dept_id, book_format, book_categories, min_price, max_price, rating)) {
      var cat;
      if (show_single_cat) {
        cat = cat_single;
      } else {
        if (book.department == "fiction") {
          cat = cat_fiction;
        } else {
          cat = cat_children;
        }
      }
      var res = new scopes.lib.CategorisedResult(cat);
      res.set_uri("uri" + count++);
      res.set_title(book.title);
      res.set_art(scopes.self.scope_directory + "/covers/" + book.department + "/" + book.art);
      res.set("subtitle", book.author);
      res.set("description", book.synopsis);

      var rating_s = "☆ " + book.rating;
      var price_s = "£" + book.price;

      res.set("price", price_s);
      res.set("rating", rating_s);

      res.set("attributes", [{value: price_s}, {value: rating_s}]);

      // Push the result
      if (!reply.push(res)) {
        return;
      }
    }
  }
}

scopes.self.initialize(
      {}
      ,
      {
        run: function() {
          console.log('Running...')
        },
        start: function(scope_id) {
          console.log('Starting scope id: '
                      + scope_id
                      + ', '
                      + scopes.self.scope_directory)
        },
        search: function(canned_query, metadata) {
          return new scopes.lib.SearchQuery(
                canned_query,
                metadata,
                // run
                function(search_reply) {
                  var query_string = canned_query.query_string();
                  var dept_id = canned_query.department_id();
                  var filter_state = canned_query.filter_state();

                  // departments
                  var root = new scopes.lib.Department("", canned_query, "All Books");
                  root.add_subdepartment(new scopes.lib.Department("fiction", canned_query, "Fiction"));
                  root.add_subdepartment(new scopes.lib.Department("childrens", canned_query, "Children's"));
                  search_reply.register_departments(root);

                  var group = new scopes.lib.FilterGroup("group1", "Params");
                  var price_filter = new scopes.lib.RangeInputFilter("price", "Min", "", "to", "Max", "", group);
                  price_filter.set_title("Price range");

                  var rating_filter_labels = new scopes.lib.ValueSliderLabels("1", "5", [[2, "2"], [3, "3"], [4, "4"]]);
                  var rating_filter = new scopes.lib.ValueSliderFilter("rating", 1, 5, 1, rating_filter_labels, group);
                  rating_filter.set_title("Rating");

                  var category_filter = new scopes.lib.OptionSelectorFilter("bookcategory", "Top picks", true);
                  category_filter.add_option("book of the month", "Book of the month");
                  category_filter.add_option("bestseller", "Bestsellers");
                  category_filter.add_option("special edition", "Special editions");
                  category_filter.add_option("recommended", "Recommended");

                  var format_filter = new scopes.lib.OptionSelectorFilter("format", "Format", false);
                  format_filter.add_option("hardback", "Hardcover");
                  format_filter.add_option("paperback", "Paperback");
                  format_filter.add_option("audiobook", "Audiobook");

                  var book_format = "";
                  var book_categories = [];
                  var min_price = 0;
                  var max_price = 9999;
                  var rating = 0;

                  search_reply.push([category_filter, format_filter, price_filter, rating_filter], filter_state);

                  // determine filter values
                  var format = format_filter.active_options(filter_state);
                  if (format.length)
                  {
                    book_format = format[0].id();
                  }

                  if (price_filter.has_start_value(filter_state))
                  {
                    min_price = price_filter.start_value(filter_state);
                  }

                  if (price_filter.has_end_value(filter_state))
                  {
                    max_price = price_filter.end_value(filter_state);
                  }

                  if (rating_filter.has_value(filter_state))
                  {
                    rating = rating_filter.value(filter_state);
                  }

                  if (category_filter.has_active_option(filter_state))
                  {
                    var cats = category_filter.active_options(filter_state);
                    for (var i = 0; i < cats.length; i++)
                    {
                      book_categories.push(cats[i].id());
                    }
                  }

                  generate_results(canned_query, search_reply, book_format, book_categories, min_price, max_price, rating);

                  search_reply.finished();
                },
                // cancelled
                function() {
                });
        },
        preview: function(result, action_metadata) {
          return new scopes.lib.PreviewQuery(
                result,
                action_metadata,
                // run
                function(preview_reply) {
                  var layout1col = new scopes.lib.ColumnLayout(1);
                  var layout2col = new scopes.lib.ColumnLayout(2);
                  var layout3col = new scopes.lib.ColumnLayout(3);

                  layout1col.add_column(["image", "header", "summary", "buttons"]);

                  layout2col.add_column(["image"]);
                  layout2col.add_column(["header", "summary", "buttons"]);

                  layout3col.add_column(["image"]);
                  layout3col.add_column(["header", "summary", "buttons"]);
                  layout3col.add_column([]);

                  preview_reply.register_layout([layout1col, layout2col, layout3col]);

                  var header = new scopes.lib.PreviewWidget("header", "header");
                  header.add_attribute_value(
                        "attributes",
                        [
                          {
                            "value": result.get("price")
                          },
                          {
                            "value": result.get("rating")
                          }
                        ]
                        );
                  header.add_attribute_mapping("title", "title");
                  header.add_attribute_mapping("subtitle", "subtitle");

                  var image = new scopes.lib.PreviewWidget("image", "image");
                  image.add_attribute_mapping("source", "art");

                  var description = new scopes.lib.PreviewWidget("summary", "text");
                  description.add_attribute_mapping("text", "description");

                  var buttons = new scopes.lib.PreviewWidget("buttons", "actions");
                  buttons.add_attribute_value(
                        "actions",
                        [
                          {
                            "id": "close",
                            "label": "Close"
                          }
                        ]
                        );

                  preview_reply.push([image, header, description, buttons ]);
                  preview_reply.finished();

                },
                // cancelled
                function() {
                });
        },
        perform_action: function(result, metadata, widget_id, action_id) {
          return new scopes.lib.ActivationQuery(
                result,
                metadata,
                widget_id,
                action_id,
                // activate
                function() {
                  var activation_response;

                  switch (action_id)
                  {
                    case 'close':
                      activation_response = new scopes.lib.ActivationResponse(
                            scopes.defs.ActivationResponseStatus.ShowDash);
                      break;
                    default:
                      activation_response = new scopes.lib.ActivationResponse(
                            scopes.defs.ActivationResponseStatus.NotHandled);
                      break;
                  }

                  return activation_response;
                },
                // cancelled
                function() {
                });
        }
      }
      );

