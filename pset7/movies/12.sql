SELECT movies.title FROM movies
WHERE movies.id IN(SELECT movie_id FROM stars WHERE person_id =
(SELECT people.id FROM people WHERE name = "Johnny Depp")) AND movies.id IN (SELECT movie_id FROM stars WHERE person_id =
(SELECT people.id FROM people WHERE name = "Helena Bonham Carter"));






