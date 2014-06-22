#ifndef ANDROIDCOMPILE_H
#define ANDROIDCOMPILE_H
#include <QObject>
#include <QString>
#include <QProcessEnvironment>

class AndroidCompile : public QObject
{
    Q_OBJECT
public:
    AndroidCompile();

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
    void setCoverImageName(QString path);

    /**
     * @brief Starts compilation proccess
     */
    void startCompilation();

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
    QString _template_path;
    QString _android_sdk_path;
    QString _output_apk_name;
    QString _ant_path;
    QString _input_epub_name;
    QString _cover_image_name;
    QString _jdk_path;

    QString _package_name;
    QString _book_name;

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

    void copyProjectTemplate();
};

#endif // ANDROIDCOMPILE_H
