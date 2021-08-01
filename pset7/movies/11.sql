SELECT title FROM movies
JOIN ratings ON movies.id = ratings.movie_id
JOIN stars ON movies.id = stars.movie_id
WHERE stars.person_id = (SELECT people.id FROM people WHERE name = "Chadwick Boseman") 
order by rating DESC LIMIT 5;
