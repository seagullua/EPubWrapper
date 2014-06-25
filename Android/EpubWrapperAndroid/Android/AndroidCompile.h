#ifndef ANDROIDCOMPILE_H
#define ANDROIDCOMPILE_H
#include <QObject>
#include <QString>
#include <QProcessEnvironment>
#include <QPixmap>
#include <QThread>

class AndroidCompile : public QObject
{
    Q_OBJECT
public slots:
    /**
     * @brief Starts compilation proccess
     */
    void startCompilation();
    void startCompilationAsync();
public:
    AndroidCompile();

    void cancel();
    void waitUntilCanceled();

    /**
     * @brief Path where template of Android project is located
     * @param path
     */
    void setTemplatePath(QString path);

    /**
     * @brief Path of Android SDK
     * @param path
     */
    void setAndroidSdkPath(QString path);

    /**
     * @brief Path and file name of Apk file to produce
     * @param path
     */
    void setOutputApkName(QString path);

    /**
     * @brief Path where ant is located
     * @param path
     */
    void setAntPath(QString path);

    /**
     * @brief Package name to use while compilation
     * @param path
     */
    void setPackageName(QString name);

    /**
     * @brief The name of the book
     * @param path
     */
    void setBookName(QString name);

    /**
     * @brief The name of the Epub to wrapp
     * @param path
     */
    void setInputEpub(QString path);

    /**
     * @brief The name of image with cover
     * @param path
     */
    void setCoverImage(QPixmap image);



    /**
     * @brief Java Development Kit path
     */
    void setJdkPath(QString path);
signals:
    void progress(int steps_made, int steps_all);
    void logMessage(QString message);
    void warningMessage(QString message);
    void errorMessage(QString message);
    void finished(bool success, QString text);
private:
    bool _terminate;
    QString _template_path;
    QString _android_sdk_path;
    QString _output_apk_name;
    QString _ant_path;
    QString _input_epub_name;
    QImage _cover_image;
    bool _default_cover;
    bool _is_running;
    QString _jdk_path;

    QString _package_name;
    QString _book_name;
    int _steps_made;

    //Internal
    QString _build_dir;
    QProcessEnvironment _environment;

    /**
     * @brief configures _environment with PATH atributes for all dependant dirs
     */
    void prepareEnvironment();

    /**
     * @brief creates Tmp directory to put files in
     */
    void prepareOutputDir();

    /**
     * @brief deletes Tmp directory
     */
    void cleanOutputDir();

    /**
     * @brief Copies project template to target directory
     */
    void copyProjectTemplate();

    /**
     * @brief Create cover images for project
     */
    void createProjectCoverImages();
    void createCoverImage(QString icon_folder, int icon_size);

    /**
     * @brief Applies book and package name for template
     */
    void applyPackageAndBookName();

    void copyEpub();
    void buildApk();
    void copyFinalApk();
    void stepFinished();

    QThread _thread;
};

#endif // ANDROIDCOMPILE_H
