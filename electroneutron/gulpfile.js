var gulp = require('gulp'),
    typescript = require('gulp-tsc');

gulp.task('default', ['compile']);
gulp.task('compile', ['compile-ts']);
gulp.task('compile-ts', function () {
    gulp.src('server/**/*.ts')
        .pipe(typescript())
        .pipe(gulp.dest('server/'));
});